#include "rimfile.h"

#include <boost/algorithm/string.hpp>

namespace fs = boost::filesystem;

namespace reone {

namespace resources {

static const int kSignatureSize = 8;
static const char kSignature[] = "RIM V1.0";

RimFile::RimFile() : BinaryFile(kSignatureSize, kSignature) {
}

void RimFile::doLoad() {
    ignore(4);

    _resourceCount = readUint32();
    _resourcesOffset = readUint32();

    loadResources();
}

void RimFile::loadResources() {
    _resources.reserve(_resourceCount);
    seek(_resourcesOffset);

    for (int i = 0; i < _resourceCount; ++i) {
        _resources.push_back(readResource());
    }
}

RimFile::Resource RimFile::readResource() {
    std::string resRef(readFixedString(16));
    uint16_t type = readUint16();
    ignore(4 + 2);
    uint32_t offset = readUint32();
    uint32_t size = readUint32();

    Resource res;
    res.resRef = boost::to_lower_copy(resRef);
    res.type = static_cast<ResourceType>(type);
    res.offset = offset;
    res.size = size;

    return std::move(res);
}

bool RimFile::supports(ResourceType type) const {
    return true;
}

std::shared_ptr<ByteArray> RimFile::find(const std::string &resRef, ResourceType type) {
    std::string lcResRef(boost::to_lower_copy(resRef));

    auto it = std::find_if(
        _resources.begin(),
        _resources.end(),
        [&](const Resource &res) { return res.resRef == lcResRef && res.type == type; });

    if (it == _resources.end()) return nullptr;

    return std::make_shared<ByteArray>(getResourceData(*it));
}

ByteArray RimFile::getResourceData(const Resource &res) {
    return readArray<char>(res.offset, res.size);
}

ByteArray RimFile::getResourceData(int idx) {
    if (idx >= _resourceCount) {
        throw std::logic_error("RIM: resource index out of range: " + std::to_string(idx));
    }
    return getResourceData(_resources[idx]);
}

const std::vector<RimFile::Resource> &RimFile::resources() const {
    return _resources;
}

} // namespace resources

} // namespace reone

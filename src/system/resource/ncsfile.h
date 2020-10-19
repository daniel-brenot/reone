/*
 * Copyright � 2020 Vsevolod Kremianskii
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <memory>
#include <string>

#include "binfile.h"

#include "../script/program.h"

namespace reone {

namespace resource {

/**
 * Parses compiled script program.
 *
 * http://www.nynaeve.net/Skywing/nwn2/Documentation/ncs.html
 */
class NcsFile : public BinaryFile {
public:
    NcsFile(const std::string &resRef);

    void doLoad() override;

    std::shared_ptr<script::ScriptProgram> program() const;

private:
    std::string _resRef;
    std::shared_ptr<script::ScriptProgram> _program;

    void readInstruction(uint32_t &offset);
};

} // namespace resources

} // namespace reone
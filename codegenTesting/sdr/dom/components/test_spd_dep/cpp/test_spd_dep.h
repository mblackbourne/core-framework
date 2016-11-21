/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK codegenTesting.
 *
 * REDHAWK codegenTesting is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK codegenTesting is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */
#ifndef TEST_SPD_DEP_IMPL_H
#define TEST_SPD_DEP_IMPL_H

#include "test_spd_dep_base.h"

class test_spd_dep_i : public test_spd_dep_base
{
    ENABLE_LOGGING
    public:
        test_spd_dep_i(const char *uuid, const char *label);
        ~test_spd_dep_i();
        int serviceFunction();
};

#endif

/******************************************************************************
* MIT License
* 
* Copyright (c) 2021 Justin J. Jordan
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
******************************************************************************/

#pragma once

namespace Sensors {

    /**
     * @brief Interface class for a pressure sensor
     * 
     */
    class IPressure {
        
        public:

        /**
         * @brief Sensor configuration to be defined by concrete class
         * 
         */
        struct Config;

        /**
         * @brief Initialize the sensor with the given configuration
         * 
         * @param config Sensor configuration
         */
        virtual void init(Config& config) = 0;

        /**
         * @brief Get current pressure reading
         * 
         * @return float current pressure
         */
        virtual float get_pressure() = 0;

        /**
         * @brief Destroy the IPressure object
         * 
         */
        virtual ~IPressure(){}
    };
}
/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2021 John Wellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include "unit_test_framework.h"

#include <iterator>
#include <string>
#include <vector>
#include <stdint.h>

#include "etl/crc32_xfer.h"
#include "etl/endianness.h"

//*****************************************************************************
// The results for these tests were created from https://crccalc.com/
//*****************************************************************************

namespace
{
  SUITE(test_crc32_xfer)
  {
    //*************************************************************************
    // Table size 256
    //*************************************************************************
    TEST(test_crc32_xfer)
    {
      std::string data("123456789");

      uint32_t crc = etl::crc32_xfer(data.begin(), data.end());

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

#if ETL_USING_CPP14 && !defined(ETL_CRC_FORCE_CPP03_IMPLEMENTATION)
    //*************************************************************************
    TEST(test_crc32_xfer_constexpr)
    {
      constexpr char data[] = "123456789";
      constexpr uint32_t crc = etl::crc32_xfer(data, data + 9);

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }
#endif

    //*************************************************************************
    TEST(test_crc32_xfer_add_values)
    {
      std::string data("123456789");

      etl::crc32_xfer crc_calculator;

      for (size_t i = 0UL; i < data.size(); ++i)
      {
        crc_calculator.add(data[i]);
      }

      uint32_t crc = crc_calculator;

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_add_range)
    {
      std::string data("123456789");

      etl::crc32_xfer crc_calculator;

      crc_calculator.add(data.begin(), data.end());

      uint32_t crc = crc_calculator.value();

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_add_range_via_iterator)
    {
      std::string data("123456789");

      etl::crc32_xfer crc_calculator;

      std::copy(data.begin(), data.end(), crc_calculator.input());

      uint32_t crc = crc_calculator.value();

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_add_range_endian)
    {
      std::vector<uint8_t>  data1 = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
      std::vector<uint32_t> data2;
      if (etl::endianness::value() == etl::endian::little)
      {
        data2 = { 0x04030201UL, 0x08070605UL };
      }
      else
      {
        data2 = { 0x01020304UL, 0x05060708UL };
      }
      std::vector<uint8_t>  data3 = { 0x08U, 0x07U, 0x06U, 0x05U, 0x04U, 0x03U, 0x02U, 0x01U };

      uint32_t crc1 = etl::crc32_xfer(data1.begin(), data1.end());
      uint32_t crc2 = etl::crc32_xfer((uint8_t*)&data2[0], (uint8_t*)(&data2[0] + data2.size()));
      CHECK_EQUAL(crc1, crc2);

      uint32_t crc3 = etl::crc32_xfer(data3.rbegin(), data3.rend());
      CHECK_EQUAL(crc1, crc3);
    }

    //*************************************************************************
    // Table size 16
    //*************************************************************************
    TEST(test_crc32_xfer_16)
    {
      std::string data("123456789");

      uint32_t crc = etl::crc32_xfer_t16(data.begin(), data.end());

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

#if ETL_USING_CPP14
    //*************************************************************************
    TEST(test_crc32_xfer_16_constexpr)
    {
      constexpr char data[] = "123456789";
      constexpr uint32_t crc = etl::crc32_xfer_t16(data, data + 9);

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }
#endif

    //*************************************************************************
    TEST(test_crc32_xfer_16_add_values)
    {
      std::string data("123456789");

      etl::crc32_xfer_t16 crc_calculator;

      for (size_t i = 0UL; i < data.size(); ++i)
      {
        crc_calculator.add(data[i]);
      }

      uint32_t crc = crc_calculator;

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_16_add_range)
    {
      std::string data("123456789");

      etl::crc32_xfer_t16 crc_calculator;

      crc_calculator.add(data.begin(), data.end());

      uint32_t crc = crc_calculator.value();

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_16_add_range_via_iterator)
    {
      std::string data("123456789");

      etl::crc32_xfer_t16 crc_calculator;

      std::copy(data.begin(), data.end(), crc_calculator.input());

      uint32_t crc = crc_calculator.value();

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_16_add_range_endian)
    {
      std::vector<uint8_t>  data1 = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
      std::vector<uint32_t> data2;
      if (etl::endianness::value() == etl::endian::little)
      {
        data2 = { 0x04030201UL, 0x08070605UL };
      }
      else
      {
        data2 = { 0x01020304UL, 0x05060708UL };
      }
      std::vector<uint8_t>  data3 = { 0x08U, 0x07U, 0x06U, 0x05U, 0x04U, 0x03U, 0x02U, 0x01U };

      uint32_t crc1 = etl::crc32_xfer_t16(data1.begin(), data1.end());
      uint32_t crc2 = etl::crc32_xfer_t16((uint8_t*)&data2[0], (uint8_t*)(&data2[0] + data2.size()));
      CHECK_EQUAL(crc1, crc2);

      uint32_t crc3 = etl::crc32_xfer_t16(data3.rbegin(), data3.rend());
      CHECK_EQUAL(crc1, crc3);
    }

    //*************************************************************************
    // Table size 4
    //*************************************************************************
    TEST(test_crc32_xfer_4)
    {
      std::string data("123456789");

      uint32_t crc = etl::crc32_xfer_t4(data.begin(), data.end());

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

#if ETL_USING_CPP14
    //*************************************************************************
    TEST(test_crc32_xfer_4_constexpr)
    {
      constexpr char data[] = "123456789";
      constexpr uint32_t crc = etl::crc32_xfer_t4(data, data + 9);

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }
#endif

    //*************************************************************************
    TEST(test_crc32_xfer_4_add_values)
    {
      std::string data("123456789");

      etl::crc32_xfer_t4 crc_calculator;

      for (size_t i = 0UL; i < data.size(); ++i)
      {
        crc_calculator.add(data[i]);
      }

      uint32_t crc = crc_calculator;

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_4_add_range)
    {
      std::string data("123456789");

      etl::crc32_xfer_t4 crc_calculator;

      crc_calculator.add(data.begin(), data.end());

      uint32_t crc = crc_calculator.value();

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_4_add_range_via_iterator)
    {
      std::string data("123456789");

      etl::crc32_xfer_t4 crc_calculator;

      std::copy(data.begin(), data.end(), crc_calculator.input());

      uint32_t crc = crc_calculator.value();

      CHECK_EQUAL(0xBD0BE338UL, crc);
    }

    //*************************************************************************
    TEST(test_crc32_xfer_4_add_range_endian)
    {
      std::vector<uint8_t>  data1 = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
      std::vector<uint32_t> data2;
      if (etl::endianness::value() == etl::endian::little)
      {
        data2 = { 0x04030201UL, 0x08070605UL };
      }
      else
      {
        data2 = { 0x01020304UL, 0x05060708UL };
      }
      std::vector<uint8_t>  data3 = { 0x08U, 0x07U, 0x06U, 0x05U, 0x04U, 0x03U, 0x02U, 0x01U };

      uint32_t crc1 = etl::crc32_xfer_t4(data1.begin(), data1.end());
      uint32_t crc2 = etl::crc32_xfer_t4((uint8_t*)&data2[0], (uint8_t*)(&data2[0] + data2.size()));
      CHECK_EQUAL(crc1, crc2);

      uint32_t crc3 = etl::crc32_xfer_t4(data3.rbegin(), data3.rend());
      CHECK_EQUAL(crc1, crc3);
    }
  };
}


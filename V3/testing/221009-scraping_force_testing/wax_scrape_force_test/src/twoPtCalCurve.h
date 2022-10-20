// File: TwoPtCalCurve.h
// Author: David Antaki
// Date: 6/20/2020
// License: This software is not open source and is copyrighted by David
// Antaki and Sous Bois International, Inc.
// Contents: Library for a calibration curve for use with a sensor.
//
// A calibration curve is a function/graph with the theoretical values that
// the sensor SHOULD/IS EXPECTED to output on the y-axis, and the ACTUALLY
// values measured by the sensor on the x-axis.
//
// For example, if you had a temperature sensor. To calibrate it, you
// read a value from the temperature sensor and say it outputs 30F but
// the actual temperature in the room is 32F. (30, 32) becomes your first
// point on the calibration curve.
//
// On a different day (or you change the environment temperature), you take
// another reading from the temp sensor and it reads 54F, but the actual
// temp in the room is 51F. (54, 51) becomes your second point on the
// calibration curve.
//
// (30, 32) and (54, 51) would be the CalPoint's you pass when instantiating
// an object of this class.

// MIT License

// Copyright (c) 2020 David Antaki

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef TWO_PT_CAL_CURVE_H
#define TWO_PT_CAL_CURVE_H

template <typename T>
class TwoPtCalCurve
{
public:
    // A point on the xy plane
    typedef struct
    {
        T refY; // Theoretical/reference voltage
        T expX; // Experimental/measured voltage
    } CalPoint;

    // The calibration curve represented by a slope and y-intercept
    typedef struct
    {
        T slope;
        T yint;
    } CalCurve;

    TwoPtCalCurve();

    // If you picture the calibration curve graph, it should be the theoretical
    // output of the sensor graphs vs the values actually measured by the sensor.
    //
    // @param _calPt1   The first point on the calibration curve.
    // @param _calPt2   The second point on the calibration curve.
    TwoPtCalCurve(CalPoint _calPt1, CalPoint _calPt2);
    ~TwoPtCalCurve();
    // To calibrate an input value/point using the 2-pt calibration curve.
    // Uses y = mx + b where y=value returned and x=_measuredVal
    //
    // @param _measuredVal  The value measured from the sensor.
    // @return              The measured value calibrated using the 2-pt
    //                      calibration curve, inputted as x.
    T calibrateVal(T _measuredVal);

private:
    // The 2 Point calibration curve itself
    CalCurve calCurve;
};

template <typename T>
TwoPtCalCurve<T>::TwoPtCalCurve()
{
}

template <typename T>
TwoPtCalCurve<T>::TwoPtCalCurve(CalPoint _calPt1, CalPoint _calPt2)
{
    calCurve.slope = (_calPt2.refY - _calPt1.refY) / (_calPt2.expX - _calPt1.expX);
    calCurve.yint = _calPt1.refY - (calCurve.slope * _calPt1.expX);
}

template <typename T>
TwoPtCalCurve<T>::~TwoPtCalCurve()
{
}

template <typename T>
T TwoPtCalCurve<T>::calibrateVal(T _measuredVal)
{
    return (calCurve.slope * _measuredVal) + calCurve.yint;
}

#endif //TWO_PT_CAL_CURVE_H

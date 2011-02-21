// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2011, Geodan, Amsterdam, the Netherlands
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Quickbook Example

//[assign_2d_point
//` Shows the usage of assign to set point coordinates, and, besides that, shows how you can initialize ttmath points with high precision

#include <iostream>
#include <iomanip>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/extensions/contrib/ttmath_stub.hpp>


int main()
{
    using boost::geometry::assign;


    boost::geometry::model::d2::point_xy<double> p1;
    assign(p1, 1.2345, 2.3456);

    boost::geometry::model::d2::point_xy<ttmath::Big<1,4> > p2;
    assign(p2, "1.2345", "2.3456"); /*< It is possible to assign coordinates with other types than the coordinate type.
        For ttmath, you can e.g. conveniently use strings. The advantage is that it then has higher precision, because
        if doubles are used for assignments the double-precision is used.
        >*/

    std::cout
        << std::setprecision(20)
        << boost::geometry::dsv(p1) << std::endl
        << boost::geometry::dsv(p2) << std::endl;

    return 0;
}

//]


//[assign_2d_point_output
/*`
Output:
[pre
(1.2344999999999999, 2.3456000000000001)
(1.2345, 2.3456)
]
*/
//]

// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP

#include <cstddef>
#include <utility>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/geometries/helper_geometry.hpp>

#include <boost/geometry/strategies/compare.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>

#include <boost/geometry/algorithms/detail/envelope/point.hpp>
#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>

#include <boost/geometry/algorithms/detail/expand/point.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_one_segment
{
    template<typename Point, typename Box>
    static inline void apply(Point const& p1, Point const& p2, Box& mbr)
    {
        envelope_one_point<Dimension, DimensionCount>::apply(p1, mbr);
        detail::expand::point_loop
            <
                strategy::compare::default_strategy,
                strategy::compare::default_strategy,
                Dimension,
                DimensionCount
            >::apply(mbr, p2);
    }
};


// Computes the MBR of a segment given by (lon1, lat1) and (lon2,
// lat2), and with azimuths a1 and a2 at the two endpoints of the
// segment.
// It is assumed that the spherical coordinates of the segment are
// normalized and in radians.
// The longitudes and latitudes of the endpoints are overridden by
// those of the box.
class compute_mbr_of_segment
{
private:
    // computes the azimuths of the segment with endpoints (lon1, lat1)
    // and (lon2, lat2)
    template <typename CalculationType>
    static inline void azimuths(CalculationType const& lon1,
                                CalculationType const& lat1,
                                CalculationType const& lon2,
                                CalculationType const& lat2,
                                CalculationType& a1,
                                CalculationType& a2)
    {
        BOOST_GEOMETRY_ASSERT(math::smaller(lon1, lon2));

        CalculationType dlon = lon2 - lon1;
        CalculationType sin_dlon = sin(dlon);
        CalculationType cos_dlon = cos(dlon);
        CalculationType cos_lat1 = cos(lat1);
        CalculationType cos_lat2 = cos(lat2);
        CalculationType sin_lat1 = sin(lat1);
        CalculationType sin_lat2 = sin(lat2);
 
        a1 = atan2(sin_dlon * cos_lat2,
                   cos_lat1 * sin_lat2 - sin_lat1 * cos_lat2 * cos_dlon);

        a2 = atan2(-sin_dlon * cos_lat1,
                   cos_lat2 * sin_lat1 - sin_lat2 * cos_lat1 * cos_dlon);
        a2 += math::pi<CalculationType>();
   }

    template <typename CalculationType>
    static inline void swap(CalculationType& lon1,
                            CalculationType& lat1,
                            CalculationType& lon2,
                            CalculationType& lat2)
    {
        std::swap(lon1, lon2);
        std::swap(lat1, lat2);
    }

    template <typename CalculationType>
    static inline bool contains_pi_half(CalculationType const& a1,
                                        CalculationType const& a2)
    {
        // azimuths a1 and a2 are assumed to be in radians
        BOOST_GEOMETRY_ASSERT(! math::equals(a1, a2));

        static CalculationType const pi_half = math::half_pi<CalculationType>();

        return (a1 < a2)
            ? (a1 < pi_half && pi_half < a2)
            : (a1 > pi_half && pi_half > a2);
    }

    template <typename CoordinateType>
    static inline bool crosses_antimeridian(CoordinateType const& lon1,
                                            CoordinateType const& lon2)
    {
        return math::larger(math::abs(lon1 - lon2), math::pi<CoordinateType>());
    }

    template <typename CalculationType>
    static inline CalculationType max_latitude(CalculationType const& azimuth,
                                               CalculationType const& latitude)
    {
        // azimuth and latitude are assumed to be in radians
        return acos( math::abs(cos(latitude) * sin(azimuth)) );
    }

    template <typename CalculationType>
    static inline void compute_box_corners(CalculationType& lon1,
                                           CalculationType& lat1,
                                           CalculationType& lon2,
                                           CalculationType& lat2,
                                           CalculationType const& a1,
                                           CalculationType const& a2)
    {
        // coordinates are assumed to be in radians
        BOOST_GEOMETRY_ASSERT(! math::larger(lon1, lon2));

        if (math::equals(a1, a2))
        {
            // the segment must lie on the equator; nothing to do
            BOOST_GEOMETRY_ASSERT(math::equals(lat1, CalculationType(0)));
            BOOST_GEOMETRY_ASSERT(math::equals(lat2, CalculationType(0)));
            return;
        }

        if (math::larger(lat1, lat2))
        {
            std::swap(lat1, lat2);
        }

        if (contains_pi_half(a1, a2))
        {
            CalculationType mid_lat = lat1 + lat2;
            if (mid_lat < 0)
            {
                // update using min latitude
                CalculationType lat_min = -max_latitude(a1, lat1);

                if (math::larger(lat1, lat_min))
                {
                    lat1 = lat_min;
                }
            }
            else if (mid_lat > 0)
            {
                // update using max latitude
                CalculationType lat_max = max_latitude(a1, lat1);

                if (math::smaller(lat2, lat_max))
                {
                    lat2 = lat_max;
                }
            }
        }
    }

    template <typename CalculationType>
    static inline void apply(CalculationType& lon1,
                             CalculationType& lat1,
                             CalculationType& lon2,
                             CalculationType& lat2)
    {
        CalculationType const half_pi = math::half_pi<CalculationType>();

        bool is_pole1 = math::equals(math::abs(lat1), half_pi);
        bool is_pole2 = math::equals(math::abs(lat2), half_pi);

        if (is_pole1 && is_pole2)
        {
            // both points are poles; nothing more to do:
            // longitudes are already normalized to 0
            BOOST_GEOMETRY_ASSERT(lon1 == CalculationType(0)
                         &&
                         lon2 == CalculationType(0));
        }
        else if (is_pole1 && !is_pole2)
        {
            // first point is a pole, second point is not:
            // make the longitude of the first point the same as that
            // of the second point
            lon1 = lon2;
        }
        else if (!is_pole1 && is_pole2)
        {
            // second point is a pole, first point is not:
            // make the longitude of the second point the same as that
            // of the first point
            lon2 = lon1;
        }

        if (math::equals(lon1, lon2))
        {
            // segment lies on a meridian
            if (math::larger(lat1, lat2))
            {
                std::swap(lat1, lat2);
            }
            return;
        }

        BOOST_GEOMETRY_ASSERT(!is_pole1 && !is_pole2);

        if (math::larger(lon1, lon2))
        {
            swap(lon1, lat1, lon2, lat2);
        }

        if (crosses_antimeridian(lon1, lon2))
        {
            lon1 += math::two_pi<CalculationType>();
            swap(lon1, lat1, lon2, lat2);
        }

        CalculationType a1 = 0, a2 = 0;
        azimuths(lon1, lat1, lon2, lat2, a1, a2);

        compute_box_corners(lon1, lat1, lon2, lat2, a1, a2);
    }

public:
    template <typename CalculationType, typename Box>
    static inline void apply(CalculationType lon1,
                             CalculationType lat1,
                             CalculationType lon2,
                             CalculationType lat2,
                             Box& mbr)
    {
        typedef typename coordinate_type<Box>::type box_coordinate_type;

        typedef typename helper_geometry
            <
                Box, box_coordinate_type, radian
            >::type helper_box_type;

        helper_box_type radian_mbr;

        apply(lon1, lat1, lon2, lat2);

        geometry::set
            <
                min_corner, 0
            >(radian_mbr, boost::numeric_cast<box_coordinate_type>(lon1));

        geometry::set
            <
                min_corner, 1
            >(radian_mbr, boost::numeric_cast<box_coordinate_type>(lat1));

        geometry::set
            <
                max_corner, 0
            >(radian_mbr, boost::numeric_cast<box_coordinate_type>(lon2));

        geometry::set
            <
                max_corner, 1
            >(radian_mbr, boost::numeric_cast<box_coordinate_type>(lat2));

        transform_units(radian_mbr, mbr);
    }
};


template <std::size_t DimensionCount>
struct envelope_segment_on_sphere
{
    template <typename Point, typename Box>
    static inline void apply(Point const& p1, Point const& p2, Box& mbr)
    {
        // first compute the envelope range for the first two coordinates
        Point p1_normalized = detail::return_normalized<Point>(p1);
        Point p2_normalized = detail::return_normalized<Point>(p2);

        compute_mbr_of_segment::apply(geometry::get_as_radian<0>(p1_normalized),
                                      geometry::get_as_radian<1>(p1_normalized),
                                      geometry::get_as_radian<0>(p2_normalized),
                                      geometry::get_as_radian<1>(p2_normalized),
                                      mbr);

        // now compute the envelope range for coordinates of
        // dimension 2 and higher
        envelope_one_segment<2, DimensionCount>::apply(p1, p2, mbr);
    }

    template <typename Segment, typename Box>
    static inline void apply(Segment const& segment, Box& mbr)
    {
        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);
        apply(p[0], p[1], mbr);
    }
};



template <std::size_t DimensionCount, typename CS_Tag>
struct envelope_segment
    : envelope_one_segment<0, DimensionCount>
{};


template <std::size_t DimensionCount>
struct envelope_segment<DimensionCount, spherical_equatorial_tag>
    : envelope_segment_on_sphere<DimensionCount>
{};



}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment, typename CS_Tag>
struct envelope<Segment, segment_tag, CS_Tag>
{
    template <typename Box>
    static inline void apply(Segment const& segment, Box& mbr)
    {
        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);
        detail::envelope::envelope_segment
            <
                dimension<Segment>::value, CS_Tag
            >::apply(p[0], p[1], mbr);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:03:54 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/06 14:41:00 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
private:
  const Fixed x_;
  const Fixed y_;
  Point &operator=(const Point &other);

public:
  Point();
  Point(const float x, const float y);
  Point(const Point &other);
  ~Point();

  Fixed getX() const;
  Fixed getY() const;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif

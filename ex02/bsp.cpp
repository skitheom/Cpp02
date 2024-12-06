/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:02:33 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/07 00:23:57 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <cmath>
#include <iostream>

static Fixed triangleArea(Point p1, Point p2, Point p3) {

  Fixed result = (((p1.getX() - p3.getX()) * (p2.getY() - p3.getY())) -
                  ((p2.getX() - p3.getX()) * (p1.getY() - p3.getY()))) /
                 2.0f;
  return result < 0 ? result * -1 : result;
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {

  Fixed totalArea = triangleArea(a, b, c);
  Fixed area1 = triangleArea(point, b, c);
  Fixed area2 = triangleArea(a, point, c);
  Fixed area3 = triangleArea(a, b, point);

  // std::cout << "Total Area: " << totalArea << std::endl;
  // std::cout << "Area1: " << area1 << std::endl;
  // std::cout << "Area2: " << area2 << std::endl;
  // std::cout << "Area3: " << area3 << std::endl;

  const Fixed epsilon(0.01f);

  if (area1 <= epsilon || area2 <= epsilon || area3 <= epsilon) {
    // std::cout << "Point is on vertex or edge." << std::endl;
    return false;
  }

  Fixed sumOfAreas = area1 + area2 + area3;
  // std::cout << "Sum: " << sumOfAreas << std::endl;
  // std::cout << "Epsilon: " << epsilon << std::endl;
  if (std::abs((totalArea - sumOfAreas).toFloat()) <= epsilon.toFloat()) {
    return true;
  }
  return false;
}

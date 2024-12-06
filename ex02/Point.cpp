/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:03:52 by sakitaha          #+#    #+#             */
/*   Updated: 2024/12/06 14:46:07 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x_(0), y_(0) {}

Point::Point(const float x, const float y) : x_(x), y_(y) {}

Point::Point(const Point &other) : x_(other.x_), y_(other.y_) {}

Point::~Point() {}

Fixed Point::getX() const { return x_; }

Fixed Point::getY() const { return y_; }

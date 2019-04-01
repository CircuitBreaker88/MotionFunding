// Copyright (c) 2012-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The Motion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Functionality for communicating with MotionGate.
 */
#ifndef BITCOIN_MOTIONCONTROL_H
#define BITCOIN_MOTIONCONTROL_H

#include <string>

#include <boost/function.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/thread.hpp>

extern const std::string DEFAULT_MOTION_CONTROL;
static const bool DEFAULT_LISTEN_ONION = true;

void StartMotionControl(boost::thread_group& threadGroup);
void InterruptMotionControl();
void StopMotionControl();

#endif /* BITCOIN_MOTIONCONTROL_H */



/*
 * $Id$
 *
 * Copyright (C) 2013 Crocodile RCS Ltd
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Exception: permission to copy, modify, propagate, and distribute a work
 * formed by combining OpenSSL toolkit software and the code in this file,
 * such as linking with software components and libraries released under
 * OpenSSL project license.
 *
 */
#ifndef AUTHORIZE_H
#define AUTHORIZE_H

#include "../../str.h"
#include "../../parser/msg_parser.h"

int autheph_verify_timestamp(str *_username);

int autheph_check(struct sip_msg *_m, char *_realm);
int autheph_www(struct sip_msg *_m, char *_realm);
int autheph_www2(struct sip_msg *_m, char *_realm, char *_method);
int autheph_proxy(struct sip_msg *_m, char *_realm);
int autheph_authenticate(struct sip_msg *_m, char *_username, char *_password);

#endif /* AUTHORIZE_H */

/*
 * $Id$
 *
 * Copyright (C) 2001-2003 FhG Fokus
 *
 * This file is part of ser, a free SIP server.
 *
 * ser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * For a license to use the ser software under conditions
 * other than those described here, or to purchase support for this
 * software, please contact iptel.org by e-mail at the following addresses:
 *    info@iptel.org
 *
 * ser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/** @file
 * @brief Parser :: Via parsing automation
 *
 * @ingroup parser
 */

/* 
 *  2003-01-21  added rport parsing code, contributed by
 *               Maxim Sobolev  <sobomax@FreeBSD.org>
 *  2003-01-21  added extra via param parsing code (i=...), used
 *               by tcp to identify the sending socket, by andrei
 *  2003-01-27  added a new member (start) to via_param, by andrei
 *  2003-10-27  added alias to via && PARAM_ALIAS (andrei)
 *  2006-02-24  added comp/PARAM_COMP support (andrei)
 */



#ifndef PARSE_VIA_H
#define PARSE_VIA_H

#include "../str.h"

struct sip_msg;

/* via param types
 * WARNING: keep in sync with parse_via.c FIN_HIDDEN... 
 * and with tm/sip_msg.c via_body_cloner
 */
enum {
	PARAM_HIDDEN=230, PARAM_TTL, PARAM_BRANCH, 
	PARAM_MADDR, PARAM_RECEIVED, PARAM_RPORT, PARAM_I, PARAM_ALIAS,
#ifdef USE_COMP
	PARAM_COMP,
#endif
	GEN_PARAM=253,
	PARAM_ERROR
};



struct via_param {
	int type;               /* Type of the parameter */
	str name;               /* Name of the parameter */
	str value;              /* Value of the parameter */
	char* start;            /* Pointer to param start, just after ';',
							 * (it can be diff. from name.s!) */
	int size;               /* total size, including preceding and trailing
							 * white space */
	struct via_param* next; /* Next parameter in the list */
};


/* Format: name/version/transport host:port;params comment */
 /* WARNING: keep in sync with tm/sip_msg.c via_body_cloner */
struct via_body { 
	int error;
	str hdr;   /* Contains "Via" or "v" */
	str name;
	str version;   
	str transport;
	str host;
	short proto; /* transport */
	unsigned short port;
#ifdef USE_COMP
	short comp_no;
#endif
	str port_str;
	str params;
	str comment;
	int bsize;                    /* body size, not including hdr */
	struct via_param* param_lst;  /* list of parameters*/
	struct via_param* last_param; /*last via parameter, internal use*/

	     /* shortcuts to "important" params*/
	struct via_param* branch;
	str tid; /* transaction id, part of branch */
	struct via_param* received;
	struct via_param* rport;
	struct via_param* i;
	struct via_param* alias; /* alias see draft-ietf-sip-connect-reuse-00 */
#ifdef USE_COMP
	struct via_param* comp; /* see rfc3486 */
#endif
	struct via_body* next; /* pointer to next via body string if
				  compact via or null */
};


/*
 * Main Via header field parser
 */
char* parse_via(char* buffer, char* end, struct via_body *vb);


/*
 * Free allocated memory
 */
void free_via_list(struct via_body *vb);


/*
 * Get one Via header
 */
int parse_via_header( struct sip_msg *msg, int n, struct via_body** q);


#endif /* PARSE_VIA_H */

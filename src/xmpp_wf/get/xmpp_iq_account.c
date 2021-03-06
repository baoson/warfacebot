/**
 * WarfaceBot, a blind XMPP client for Warface (FPS)
 * Copyright (C) 2015, 2016 Levak Borok <levak92@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <wb_tools.h>
#include <wb_session.h>
#include <wb_xmpp.h>
#include <wb_xmpp_wf.h>
#include <wb_cvar.h>

static void xmpp_iq_account_cb(const char *msg,
                               enum xmpp_msg_type type,
                               void *args)
{
    /* Answer :
       <iq from='k01.warface' to='XXXX@warface/GameClient' type='result'>
         <query xmlns='urn:cryonline:k01'>
           <account user='XXXX' active_token='$WF_XXXX_....'
            load_balancing_type='server'>
             <masterservers>
               <server .../>
               ...
     */

    if (type & XMPP_TYPE_ERROR)
        return;

    free(session.online.active_token);
    free(session.online.id);

    session.online.status = STATUS_ONLINE;
    session.online.active_token =
        get_info(msg, "active_token='", "'", "ACTIVE TOKEN");
    session.online.id = get_info(msg, "user='", "'", NULL);

    xmpp_iq_get_master_server(cvar.online_channel_type);
}

void xmpp_iq_account(char *login)
{
    xmpp_send_iq_get(
        JID_K01,
        xmpp_iq_account_cb, NULL,
        "<query xmlns='urn:cryonline:k01'>"
        "<account login='%s'/>" /* Don't put any space there ! */
        "</query>",
        login);
}

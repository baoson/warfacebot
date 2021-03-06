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

#include <wb_session.h>
#include <wb_xmpp_wf.h>
#include <wb_mission.h>
#include <wb_list.h>

#include <string.h>

static void copy_player_name(struct gr_core_player *p, void *args)
{
    struct list *l = (struct list *) args;

    if (list_contains(l, p->nickname))
        return;

    list_add(l, strdup(p->nickname));
}

static void copy_friend_name(struct friend *p, void *args)
{
    struct list *l = (struct list *) args;

    if (list_contains(l, p->nickname))
        return;

    if (p->nickname != NULL)
        list_add(l, strdup(p->nickname));
}

static void copy_clanmate_name(struct clanmate *p, void *args)
{
    struct list *l = (struct list *) args;

    if (list_contains(l, p->nickname))
        return;

    if (p->nickname != NULL)
        list_add(l, strdup(p->nickname));
}

void complete_gameroom_players(struct list *l)
{
    if (session.gameroom.sync.core.players != NULL)
    {
        list_foreach(session.gameroom.sync.core.players,
                     (f_list_callback) copy_player_name,
                     (void *) l);
    }
}

void complete_buddies(struct list *l)
{
    if (session.profile.friends != NULL)
    {
        list_foreach(session.profile.friends,
                     (f_list_callback) copy_friend_name,
                     (void *) l);
    }

    if (session.profile.clanmates != NULL)
    {
        list_foreach(session.profile.clanmates,
                     (f_list_callback) copy_clanmate_name,
                     (void *) l);
    }
}

void complete_friends(struct list *l)
{
    if (session.profile.friends != NULL)
    {
        list_foreach(session.profile.friends,
                     (f_list_callback) copy_friend_name,
                     (void *) l);
    }
}

void complete_clanmates(struct list *l)
{
    if (session.profile.clanmates != NULL)
    {
        list_foreach(session.profile.clanmates,
                     (f_list_callback) copy_clanmate_name,
                     (void *) l);
    }
}

static void copy_mission_pvp_name(struct mission *m, void *args)
{
    struct list *l = (struct list *) args;

    if (m->mode == NULL || 0 != strcmp(m->mode, "pve"))
        list_add(l, strdup(m->name));
}

static void copy_mission_pve_name(struct mission *m, void *args)
{
    struct list *l = (struct list *) args;

    if (m->mode != NULL && 0 == strcmp(m->mode, "pve"))
        list_add(l, strdup(m->name));
}

void complete_missions_pvp(struct list *l)
{
    if (session.wf.missions != NULL)
    {
        list_foreach(session.wf.missions,
                     (f_list_callback) copy_mission_pvp_name,
                     (void *) l);
    }
}

void complete_missions_pve(struct list *l)
{
    if (session.wf.missions != NULL)
    {
        list_foreach(session.wf.missions,
                     (f_list_callback) copy_mission_pve_name,
                     (void *) l);
    }
}

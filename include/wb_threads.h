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

#ifndef WB_THREADS_H
# define WB_THREADS_H

# ifdef __MINGW32__
#  include <windows.h>
#  define sleep(x) Sleep(x)
# else
#  include <unistd.h>
# endif

# define THREAD_NAME_MAX 16

void threads_init(void);
void threads_run(void);

void thread_register_sigint_handler(void);
void *thread_close(void);

/* Readstream */

void thread_readstream_post_new_msg(char *msg);
char *thread_readstream_get_next_msg(void);
void thread_readstream_init(void);
void *thread_readstream(void *vargs);

/* Sendstream */

void thread_sendstream_post_new_msg(char *msg);
char *thread_sendstream_get_next_msg(void);
void thread_sendstream_init(void);
void *thread_sendstream(void *vargs);

/* Dispatch */

void thread_dispatch_init(void);
void *thread_dispatch(void *vargs);

/* Readline */

void thread_readline_init(void);
void *thread_readline(void *vargs);

/* Ping */

void thread_ping_init(void);
void *thread_ping(void *vargs);

#endif /* !WB_THREADS_H */
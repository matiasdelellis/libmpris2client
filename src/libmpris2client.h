/*
 *  Copyright (c) 2013 matias <mati86dl@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA 02110-1335, USA.
 */

#ifndef LIB_MPRIS2_CLIENT_H
#define LIB_MPRIS2_CLIENT_H

#include <glib-object.h>
#include "mpris2-metadata.h"

/**
 * PlaybackStatus:
 * @PLAYING: A track is currently playing.
 * @PAUSED: A track is currently paused.
 * @STOPPED: There is no track currently playing.
 *
 * The current playback status:
 * See mpris2 specification <ulink url="http://specifications.freedesktop.org/mpris-spec/latest/Player_Interface.html#Property:PlaybackStatus">PlaybackStatus</ulink>
 */
typedef enum {
	PLAYING = 1,
	PAUSED,
	STOPPED
} PlaybackStatus;

/**
 * LoopStatus:
 * @NONE: The playback will stop when there are no more tracks to play
 * @TRACK: The current track will start again from the begining once it has finished playing
 * @PLAYLIST: The playback loops through a list of tracks
 *
 * The current loop / repeat status:
 * See mpris2 specification <ulink url="http://specifications.freedesktop.org/mpris-spec/latest/Player_Interface.html#Property:LoopStatus">LoopStatus</ulink>
 */
typedef enum {
	NONE = 1,
	TRACK,
	PLAYLIST
} LoopStatus;

#define MPRIS2_TYPE_CLIENT              (mpris2_client_get_type ())
#define MPRIS2_CLIENT(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), MPRIS2_TYPE_CLIENT, Mpris2Client))
#define MPRIS2_IS_CLIENT(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MPRIS2_TYPE_CLIENT))
#define MPRIS2_CLIENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), MPRIS2_TYPE_CLIENT, Mpris2ClientClass))
#define MPRIS2_IS_CLIENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), MPRIS2_TYPE_CLIENT))
#define MPRIS2_CLIENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), MPRIS2_TYPE_CLIENT, Mpris2ClientClass))

GType mpris2_client_get_type  (void) G_GNUC_CONST;

typedef struct _Mpris2Client Mpris2Client;
typedef struct _Mpris2ClientClass Mpris2ClientClass;

struct _Mpris2ClientClass {
	GObjectClass parent_class;
	void (*connection)      (Mpris2Client *mpris2, gboolean        connected);
	void (*playback_status) (Mpris2Client *mpris2, PlaybackStatus  playback_status);
	void (*playback_tick)   (Mpris2Client *mpris2, gint            position);
	void (*metadata)        (Mpris2Client *mpris2, Mpris2Metadata *metadata);
	void (*volume)          (Mpris2Client *mpris2, gdouble         volume);
	void (*loop_status)     (Mpris2Client *mpris2, LoopStatus      loop_status);
	void (*shuffle)         (Mpris2Client *mpris2, gboolean        shuffle);
};

/*
 * Library.
 */

Mpris2Client   *mpris2_client_new (void);

const gchar    *mpris2_client_get_player                (Mpris2Client *mpris2);
void            mpris2_client_set_player                (Mpris2Client *mpris2, const gchar *player);
gboolean        mpris2_client_auto_connect              (Mpris2Client *mpris2);

gchar         **mpris2_client_get_available_players     (Mpris2Client *mpris2);

gboolean        mpris2_client_is_connected              (Mpris2Client *mpris2);

gboolean        mpris2_client_get_strict_mode           (Mpris2Client *mpris2);
void            mpris2_client_set_strict_mode           (Mpris2Client *mpris2, gboolean strict_mode);

/*
 * Interface MediaPlayer2.Player Methods
 */
void            mpris2_client_prev                      (Mpris2Client *mpris2);
void            mpris2_client_next                      (Mpris2Client *mpris2);
void            mpris2_client_pause                     (Mpris2Client *mpris2);
void            mpris2_client_play_pause                (Mpris2Client *mpris2);
void            mpris2_client_stop                      (Mpris2Client *mpris2);
void            mpris2_client_play                      (Mpris2Client *mpris2);

void            mpris2_client_seek                      (Mpris2Client *mpris2, gint offset);
void            mpris2_client_set_position              (Mpris2Client *mpris2, const gchar *track_id, gint position);
void            mpris2_client_open_uri                  (Mpris2Client *mpris2, const gchar *uri);

/*
 * Interface MediaPlayer2 Methods.
 */
void            mpris2_client_raise_player              (Mpris2Client *mpris2);
void            mpris2_client_quit_player               (Mpris2Client *mpris2);
void            mpris2_client_set_fullscreen_player     (Mpris2Client *mpris2, gboolean fullscreen);

/*
 * Interface MediaPlayer2 Properies.
 */
gboolean        mpris2_client_can_quit                  (Mpris2Client *mpris2);
gboolean        mpris2_client_can_set_fullscreen        (Mpris2Client *mpris2);
gboolean        mpris2_client_can_raise                 (Mpris2Client *mpris2);
gboolean        mpris2_client_has_tracklist_support     (Mpris2Client *mpris2);
const gchar    *mpris2_client_get_player_identity       (Mpris2Client *mpris2);
const gchar    *mpris2_client_get_player_desktop_entry  (Mpris2Client *mpris2);
gchar         **mpris2_client_get_supported_uri_schemes (Mpris2Client *mpris2);
gchar         **mpris2_client_get_supported_mime_types  (Mpris2Client *mpris2);

/*
 * Interface MediaPlayer2.Player properties.
 */
PlaybackStatus  mpris2_client_get_playback_status       (Mpris2Client *mpris2);

gdouble         mpris2_client_get_playback_rate         (Mpris2Client *mpris2);

Mpris2Metadata *mpris2_client_get_metadata              (Mpris2Client *mpris2);

gdouble         mpris2_client_get_volume                (Mpris2Client *mpris2);
void            mpris2_client_set_volume                (Mpris2Client *mpris2, gdouble volume);

gint            mpris2_client_get_position              (Mpris2Client *mpris2);
gint            mpris2_client_get_accurate_position     (Mpris2Client *mpris2);

gdouble         mpris2_client_get_minimum_rate          (Mpris2Client *mpris2);

gdouble         mpris2_client_get_maximum_rate          (Mpris2Client *mpris2);

gboolean        mpris2_client_get_can_go_next           (Mpris2Client *mpris2);

gboolean        mpris2_client_get_can_go_previous       (Mpris2Client *mpris2);

gboolean        mpris2_client_get_can_play              (Mpris2Client *mpris2);

gboolean        mpris2_client_get_can_pause             (Mpris2Client *mpris2);

gboolean        mpris2_client_get_can_seek              (Mpris2Client *mpris2);

gboolean        mpris2_client_get_can_control           (Mpris2Client *mpris2);

/*
 * Optionals Interface MediaPlayer2.Player properties.
 */
gboolean        mpris2_client_player_has_loop_status    (Mpris2Client *mpris2);
LoopStatus      mpris2_client_get_loop_status           (Mpris2Client *mpris2);
void            mpris2_client_set_loop_status           (Mpris2Client *mpris2, LoopStatus loop_status);

gboolean        mpris2_client_player_has_shuffle        (Mpris2Client *mpris2);
gboolean        mpris2_client_get_shuffle               (Mpris2Client *mpris2);
void            mpris2_client_set_shuffle               (Mpris2Client *mpris2, gboolean shuffle);

#endif
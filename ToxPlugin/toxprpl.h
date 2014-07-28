//
//  toxprpl.h
//  ToxPlugin
//
//  Created by Bjorn Magnus Mathisen on 21/02/14.
//  Copyright (c) 2014 Bjorn Magnus Mathisen. All rights reserved.
//

#ifndef ToxPlugin_toxprpl_h
#define ToxPlugin_toxprpl_h

#ifdef HAVE_CONFIG_H
#include "autoconfig.h"
#endif

#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#ifndef O_BINARY
#ifdef _O_BINARY
#define O_BINARY _O_BINARY
#else
#define O_BINARY 0
#endif
#endif

#include <sys/stat.h>
#include <fcntl.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <tox/tox.h>
#include <tox/network.h>

/*#ifndef PURPLE_PLUGINS
#	define PURPLE_PLUGINS
#endif*/
#define PURPLE_STATIC_PRPL

#include <account.h>
#include <accountopt.h>
#include <blist.h>
#include <cmds.h>
#include <conversation.h>
#include <connection.h>
#include <debug.h>
#include <notify.h>
#include <privacy.h>
#include <prpl.h>
#include <roomlist.h>
#include <request.h>
#include <status.h>
#include <util.h>
#include <version.h>

#define _(msg) msg // might add gettext later

#define TOXPRPL_ID "prpl-adium-tox"
#define DEFAULT_SERVER_KEY "951C88B7E75C867418ACDB5D273821372BB5BD652740BCDF623A4FA293E75D2F"
#define DEFAULT_SERVER_PORT 33445
#define DEFAULT_SERVER_IP   "192.254.75.98"
#define VERSION "0.1337"
#define PACKAGE_URL "http://github.com/"

#define DEFAULT_REQUEST_MESSAGE _("Please allow me to add you as a friend!")

#define MAX_ACCOUNT_DATA_SIZE   1*1024*1024

#define DEFAULT_NICKNAME    "ToxedPidgin"

#define toxprpl_return_val_if_fail(expr,val)     \
if (!(expr))                                 \
{                                            \
return (val);                            \
}

#define toxprpl_return_if_fail(expr)             \
if (!(expr))                                 \
{                                            \
return;                                  \
}


#define TOXPRPL_MAX_STATUS          4
#define TOXPRPL_STATUS_ONLINE       0
#define TOXPRPL_STATUS_AWAY         1
#define TOXPRPL_STATUS_BUSY         2
#define TOXPRPL_STATUS_OFFLINE      3




    typedef struct
    {
        PurpleStatusPrimitive primitive;
        int tox_status;
        gchar *id;
        gchar *title;
    } toxprpl_status;
    
    typedef struct
    {
        int tox_friendlist_number;
    } toxprpl_buddy_data;
    
    typedef struct
    {
        PurpleConnection *gc;
        char *buddy_key;
    } toxprpl_accept_friend_data;
    
    typedef struct
    {
        Tox *tox;
        guint tox_timer;
        guint connection_timer;
        guint connected;
        PurpleCmdId myid_command_id;
        PurpleCmdId nick_command_id;
    } toxprpl_plugin_data;
    
    typedef struct
    {
        PurpleXfer *xfer;
        uint8_t *buffer;
        uint8_t *offset;
        gboolean running;
    } toxprpl_idle_write_data;
    
    typedef struct
    {
        Tox *tox;
        int friendnumber;
        uint8_t filenumber;
        toxprpl_idle_write_data *idle_write_data;
    } toxprpl_xfer_data;
    
    
    
    static toxprpl_status toxprpl_statuses[] =
    {
        {
            PURPLE_STATUS_AVAILABLE, TOXPRPL_STATUS_ONLINE,
            "tox_online", _("Online")
        },
        {
            PURPLE_STATUS_AWAY, TOXPRPL_STATUS_AWAY,
            "tox_away", _("Away")
        },
        {
            PURPLE_STATUS_UNAVAILABLE, TOXPRPL_STATUS_BUSY,
            "tox_busy", _("Busy")
        },
        {
            PURPLE_STATUS_OFFLINE, TOXPRPL_STATUS_OFFLINE,
            "tox_offline", _("Offline")
        }
    };
    
    typedef struct
    {
        char *from;
        char *message;
        time_t mtime;
        PurpleMessageFlags flags;
    } GOfflineMessage;
    
    
  static void toxprpl_add_to_buddylist(toxprpl_accept_friend_data *data);
    static void toxprpl_do_not_add_to_buddylist(toxprpl_accept_friend_data *data);
    
    static void toxprpl_login(PurpleAccount *acct);
    static void toxprpl_query_buddy_info(gpointer data, gpointer user_data);
    static void toxprpl_set_status(PurpleAccount *account, PurpleStatus *status);
    static PurpleXfer *toxprpl_new_xfer_receive(PurpleConnection *gc,
                                                const char *who, int friendnumber, int filenumber, const goffset filesize,
                                                const char *filename);
    static GList *toxprpl_status_types(PurpleAccount *acct);
    static void toxprpl_close(PurpleConnection *gc);
    static unsigned int toxprpl_send_typing(PurpleConnection *gc, const char *who,
                                            PurpleTypingState state);
    static void toxprpl_add_buddy(PurpleConnection *gc, PurpleBuddy *buddy,
                                  PurpleGroup *group, const char *msg);
    static const char *toxprpl_list_icon(PurpleAccount *acct, PurpleBuddy *buddy);
    static int toxprpl_send_im(PurpleConnection *gc, const char *who,
                               const char *message, PurpleMessageFlags flags);
    static void toxprpl_remove_buddy(PurpleConnection *gc, PurpleBuddy *buddy,
                                     PurpleGroup *group);
    static void toxprpl_free_buddy(PurpleBuddy *buddy);
    static void toxprpl_send_file(PurpleConnection *gc, const char *who, const char *filename);
    static gboolean toxprpl_can_receive_file(PurpleConnection *gc, const char *who);
    static PurpleXfer *toxprpl_new_xfer(PurpleConnection *gc, const gchar *who);
    static gboolean toxprpl_offline_message(const PurpleBuddy *buddy);
    static GList *toxprpl_account_actions(PurplePlugin *plugin, gpointer context);
    static int toxprpl_get_status_index(Tox *tox, int fnum, TOX_USERSTATUS status);

   




#endif

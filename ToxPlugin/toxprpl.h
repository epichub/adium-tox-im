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
#ifdef __WIN32__
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

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
#include <network.h>

#define PURPLE_PLUGINS

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

#define TOXPRPL_ID "prpl-jin_eld-tox"
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



extern "C" {
    static const char *g_HEX_CHARS = "0123456789abcdef";
    
    GHashTable* goffline_messages = NULL;
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

    static PurplePluginProtocolInfo prpl_info =
    {
        (PurpleProtocolOptions)  (OPT_PROTO_NO_PASSWORD | OPT_PROTO_REGISTER_NOSCREENNAME | OPT_PROTO_INVITE_MESSAGE),  /* options */
        NULL,                               /* user_splits, initialized in toxprpl_init() */
        NULL,                               /* protocol_options, initialized in toxprpl_init() */
        {"png,jpeg",0,0,64,64,0,PURPLE_ICON_SCALE_DISPLAY},                     /* icon spec */
        toxprpl_list_icon,                  /* list_icon */
        NULL,                               /* list_emblem */
        NULL,                               /* status_text */
        NULL,                               /* tooltip_text */
        toxprpl_status_types,               /* status_types */
        NULL,                               /* blist_node_menu */
        NULL,                               /* chat_info */
        NULL,                               /* chat_info_defaults */
        toxprpl_login,                      /* login */
        toxprpl_close,                      /* close */
        toxprpl_send_im,                    /* send_im */
        NULL,                               /* set_info */
        toxprpl_send_typing,                /* send_typing */
        NULL,                               /* get_info */
        toxprpl_set_status,                 /* set_status */
        NULL,                               /* set_idle */
        NULL,                               /* change_passwd */
        NULL,                               /* add_buddy */
        NULL,                               /* add_buddies */
        toxprpl_remove_buddy,               /* remove_buddy */
        NULL,                               /* remove_buddies */
        NULL,                               /* add_permit */
        NULL,                               /* add_deny */
        NULL,                               /* rem_permit */
        NULL,                               /* rem_deny */
        NULL,                               /* set_permit_deny */
        NULL,                               /* join_chat */
        NULL,                               /* reject_chat */
        NULL,                               /* get_chat_name */
        NULL,                               /* chat_invite */
        NULL,                               /* chat_leave */
        NULL,                               /* chat_whisper */
        NULL,                               /* chat_send */
        NULL,                               /* keepalive */
        NULL,                               /* register_user */
        NULL,                               /* get_cb_info */
        NULL,                               /* get_cb_away */
        NULL,                               /* alias_buddy */
        NULL,                               /* group_buddy */
        NULL,                               /* rename_group */
        toxprpl_free_buddy,                 /* buddy_free */
        NULL,                               /* convo_closed */
        NULL,                               /* normalize */
        NULL,                               /* set_buddy_icon */
        NULL,                               /* remove_group */
        NULL,                               /* get_cb_real_name */
        NULL,                               /* set_chat_topic */
        NULL,                               /* find_blist_chat */
        NULL,                               /* roomlist_get_list */
        NULL,                               /* roomlist_cancel */
        NULL,                               /* roomlist_expand_category */
        toxprpl_can_receive_file,           /* can_receive_file */
        toxprpl_send_file,                  /* send_file */
        toxprpl_new_xfer,                   /* new_xfer */
        toxprpl_offline_message,            /* offline_message */
        NULL,                               /* whiteboard_prpl_ops */
        NULL,                               /* send_raw */
        NULL,                               /* roomlist_room_serialize */
        NULL,                               /* unregister_user */
        NULL,                               /* send_attention */
        NULL,                               /* get_attention_types */
        sizeof(PurplePluginProtocolInfo),   /* struct_size */
        NULL,                               /* get_account_text_table */
        NULL,                               /* initiate_media */
        NULL,                               /* get_media_caps */
        NULL,                               /* get_moods */
        NULL,                               /* set_public_alias */
        NULL,                               /* get_public_alias */
        toxprpl_add_buddy,                  /* add_buddy_with_invite */
        NULL                                /* add_buddies_with_invite */
    };
    
    static void toxprpl_init(PurplePlugin *plugin)
    {
        purple_debug_info("toxprpl", "starting up\n");
        
        PurpleAccountOption *option = purple_account_option_string_new(
                                                                       _("Nickname"), "nickname", "");
        prpl_info.protocol_options = g_list_append(NULL, option);
        
        option = purple_account_option_string_new(
                                                  _("Server"), "dht_server", DEFAULT_SERVER_IP);
        prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
                                                   option);
        
        option = purple_account_option_int_new(_("Port"), "dht_server_port",
                                               DEFAULT_SERVER_PORT);
        prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
                                                   option);
        
        option = purple_account_option_string_new(_("Server key"),
                                                  "dht_server_key", DEFAULT_SERVER_KEY);
        prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
                                                   option);
        purple_debug_info("toxprpl", "initialization complete\n");
    }
    
    static PurplePluginInfo info =
    {
        PURPLE_PLUGIN_MAGIC,                                /* magic */
        PURPLE_MAJOR_VERSION,                               /* major_version */
        PURPLE_MINOR_VERSION,                               /* minor_version */
        PURPLE_PLUGIN_PROTOCOL,                             /* type */
        NULL,                                               /* ui_requirement */
        0,                                                  /* flags */
        NULL,                                               /* dependencies */
        PURPLE_PRIORITY_DEFAULT,                            /* priority */
        TOXPRPL_ID,                                         /* id */
        "Tox",                                              /* name */
        VERSION,                                            /* version */
        "Tox Protocol Plugin",                              /* summary */
        "Tox Protocol Plugin http://tox.im/",              /* description */
        "Sergey 'Jin' Bostandzhyan",                        /* author */
        PACKAGE_URL,                                        /* homepage */
        NULL,                                               /* load */
        NULL,                                               /* unload */
        NULL,                                               /* destroy */
        NULL,                                               /* ui_info */
        &prpl_info,                                         /* extra_info */
        NULL,                                               /* prefs_info */
        toxprpl_account_actions,                            /* actions */
        NULL,                                               /* padding... */
        NULL,
        NULL,
        NULL,
    };
    
    PURPLE_INIT_PLUGIN(tox, toxprpl_init, info);


}


#endif

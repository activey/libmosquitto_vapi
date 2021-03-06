/* example_sub.c generated by valac 0.42.5, the Vala compiler
 * generated from example_sub.vala, do not modify */



#include <glib.h>
#include <glib-object.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>

#define _mosquitto_destroy0(var) ((var == NULL) ? NULL : (var = (mosquitto_destroy (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))



void my_message_callback (struct mosquitto* client,
                          void* userdata,
                          struct mosquitto_message* message);
void my_connect_callback (struct mosquitto* client,
                          void* userdata,
                          gint _result_);
void my_subscribe_callback (struct mosquitto* client,
                            void* userdata,
                            gint mid,
                            gint qos_count,
                            gint* granted_qos,
                            int granted_qos_length1);
void my_log_callback (struct mosquitto* client,
                      void* userdata,
                      gint level,
                      const gchar* str);
gint _vala_main (gchar** args,
                 int args_length1);
static void _my_log_callback_on_log (struct mosquitto* client,
                              void* obj,
                              gint level,
                              const gchar* str);
static void _my_connect_callback_on_connect (struct mosquitto* client,
                                      void* obj,
                                      gint rc);
static void _my_message_callback_on_message (struct mosquitto* client,
                                      void* obj,
                                      struct mosquitto_message* message);
static void _my_subscribe_callback_on_subscribe (struct mosquitto* client,
                                          void* obj,
                                          gint mid,
                                          gint qos_count,
                                          gint* granted_qos);


void
my_message_callback (struct mosquitto* client,
                     void* userdata,
                     struct mosquitto_message* message)
{
	struct mosquitto_message _tmp0_;
	gint _tmp1_;
	g_return_if_fail (client != NULL);
	g_return_if_fail (message != NULL);
	_tmp0_ = *message;
	_tmp1_ = _tmp0_.payloadlen;
	if (_tmp1_ != 0) {
		struct mosquitto_message _tmp2_;
		const gchar* _tmp3_;
		struct mosquitto_message _tmp4_;
		const gchar* _tmp5_;
		_tmp2_ = *message;
		_tmp3_ = _tmp2_.topic;
		_tmp4_ = *message;
		_tmp5_ = _tmp4_.payload;
		g_print ("%s %s\n", _tmp3_, _tmp5_);
	} else {
		struct mosquitto_message _tmp6_;
		const gchar* _tmp7_;
		_tmp6_ = *message;
		_tmp7_ = _tmp6_.topic;
		g_print ("%s (null)\n", _tmp7_);
	}
}


void
my_connect_callback (struct mosquitto* client,
                     void* userdata,
                     gint _result_)
{
	g_return_if_fail (client != NULL);
	if (_result_ == 0) {
		mosquitto_subscribe (client, NULL, "$SYS/#", 2);
	} else {
		const gchar* _tmp0_;
		_tmp0_ = mosquitto_strerror (_result_);
		g_print ("Connect failed: %s\n", _tmp0_);
	}
}


void
my_subscribe_callback (struct mosquitto* client,
                       void* userdata,
                       gint mid,
                       gint qos_count,
                       gint* granted_qos,
                       int granted_qos_length1)
{
	gint i = 0;
	gint _tmp0_;
	g_return_if_fail (client != NULL);
	_tmp0_ = granted_qos[0];
	g_print ("Subscribed (mid: %d): %d", mid, _tmp0_);
	{
		gboolean _tmp1_ = FALSE;
		i = 1;
		_tmp1_ = TRUE;
		while (TRUE) {
			gint _tmp3_;
			gint _tmp4_;
			gint _tmp5_;
			if (!_tmp1_) {
				gint _tmp2_;
				_tmp2_ = i;
				i = _tmp2_ + 1;
			}
			_tmp1_ = FALSE;
			_tmp3_ = i;
			if (!(_tmp3_ < qos_count)) {
				break;
			}
			_tmp4_ = i;
			_tmp5_ = granted_qos[_tmp4_];
			g_print (", %d", _tmp5_);
		}
	}
	g_print ("\n");
}


void
my_log_callback (struct mosquitto* client,
                 void* userdata,
                 gint level,
                 const gchar* str)
{
	g_return_if_fail (client != NULL);
	g_return_if_fail (str != NULL);
	g_print ("my_log_callback: %s\n", str);
}


static void
_my_log_callback_on_log (struct mosquitto* client,
                         void* obj,
                         gint level,
                         const gchar* str)
{
	my_log_callback (client, obj, level, str);
}


static void
_my_connect_callback_on_connect (struct mosquitto* client,
                                 void* obj,
                                 gint rc)
{
	my_connect_callback (client, obj, rc);
}


static void
_my_message_callback_on_message (struct mosquitto* client,
                                 void* obj,
                                 struct mosquitto_message* message)
{
	my_message_callback (client, obj, message);
}


static void
_my_subscribe_callback_on_subscribe (struct mosquitto* client,
                                     void* obj,
                                     gint mid,
                                     gint qos_count,
                                     gint* granted_qos)
{
	my_subscribe_callback (client, obj, mid, qos_count, granted_qos, -1);
}


gint
_vala_main (gchar** args,
            int args_length1)
{
	gint result = 0;
	gint port = 0;
	gint keepalive = 0;
	gboolean clean_session = FALSE;
	gchar* host = NULL;
	gchar* _tmp0_;
	struct mosquitto* client = NULL;
	gboolean _tmp1_;
	struct mosquitto* _tmp2_;
	struct mosquitto* _tmp3_;
	struct mosquitto* _tmp4_;
	struct mosquitto* _tmp5_;
	struct mosquitto* _tmp6_;
	struct mosquitto* _tmp7_;
	const gchar* _tmp8_;
	gint _tmp9_;
	gint _tmp10_;
	struct mosquitto* _tmp11_;
	port = 1883;
	keepalive = 60;
	clean_session = TRUE;
	_tmp0_ = g_strdup ("test.mosquitto.org");
	host = _tmp0_;
	mosquitto_lib_init ();
	_tmp1_ = clean_session;
	_tmp2_ = mosquitto_new (NULL, _tmp1_, NULL);
	client = _tmp2_;
	_tmp3_ = client;
	mosquitto_log_callback_set (_tmp3_, _my_log_callback_on_log);
	_tmp4_ = client;
	mosquitto_connect_callback_set (_tmp4_, _my_connect_callback_on_connect);
	_tmp5_ = client;
	mosquitto_message_callback_set (_tmp5_, _my_message_callback_on_message);
	_tmp6_ = client;
	mosquitto_subscribe_callback_set (_tmp6_, _my_subscribe_callback_on_subscribe);
	_tmp7_ = client;
	_tmp8_ = host;
	_tmp9_ = port;
	_tmp10_ = keepalive;
	if (mosquitto_connect (_tmp7_, _tmp8_, _tmp9_, _tmp10_) != 0) {
		g_print ("Unable to connect.\n");
		result = 1;
		_mosquitto_destroy0 (client);
		_g_free0 (host);
		return result;
	}
	_tmp11_ = client;
	mosquitto_loop_forever (_tmp11_, -1, 1);
	mosquitto_lib_cleanup ();
	result = 0;
	_mosquitto_destroy0 (client);
	_g_free0 (host);
	return result;
}


int
main (int argc,
      char ** argv)
{
	return _vala_main (argv, argc);
}




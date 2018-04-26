#include <MainPage.h>



typedef struct _item_data
{
	int index;
	Elm_Object_Item *item;
} item_data;

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}
static Eina_Bool
naviframe_pop_cb(void *data, Elm_Object_Item *it)
{
	ui_app_exit();
	return EINA_FALSE;
}
static Eina_Bool
naviframe_pop_cb_webview(void *data, Elm_Object_Item *it)
{

	//ui_app_exit();
	//return EINA_FALSE;

   appdata_s *ad = (appdata_s *)data;
   Evas_Object *web = elm_object_item_data_get(it);
   ewk_view_visibility_set(web, false);
   evas_object_focus_set(ad->nf, true);
   evas_object_focus_set(ad->win, true);
   evas_object_focus_set(ad->genlist, true);
   dlog_print(DLOG_INFO, "Nishanth", "webview focus %d",ewk_view_focus_get(web));
   evas_object_del(ad->genlist);
   free(ad->genlist);
   create_list_view(ad,false);
   evas_object_del(web);
   evas_object_del(ad->webview);
   evas_object_del(ad->more_button);
   free(web);
   //evas_object_show(ad->layout);

   //evas_object_show(ad->genlist);
   //ewk_view_back_possible(o)


}
static void
btn_prev_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	if( ewk_view_back_possible( ad->webview ) == EINA_TRUE )
		ewk_view_back( ad->webview );
}

static void
btn_next_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s* ad = data;
	if( ewk_view_forward_possible( ad->webview ) == EINA_TRUE )
		ewk_view_forward( ad->webview );
}

static void
_more_item_clicked(void *data, Evas_Object *obj, void *event_info)
{
	Eext_Object_Item *item = (Eext_Object_Item *)event_info;
	const char *main_text;
	const char *sub_text;

	/* Get the text in item text part */
	main_text = eext_more_option_item_part_text_get(item, "selector,main_text");
	appdata_s* ad = data;
	if (!strcmp(main_text, "Go Back")) {
		if( ewk_view_back_possible( ad->webview ) == EINA_TRUE )
				ewk_view_back( ad->webview );

	}else if (!strcmp(main_text, "Go Forward")) {
		if( ewk_view_forward_possible( ad->webview ) == EINA_TRUE )
				ewk_view_forward( ad->webview );

	}else if(!strcmp(main_text, "Show List")) {
		//evas_object_hide(ad->webview);
		elm_naviframe_item_pop(ad->nf);
		elm_naviframe_item_pop(ad->nf);
		elm_naviframe_item_pop(ad->nf);
		elm_naviframe_item_pop(ad->nf);
		create_list_view(ad,true);
		evas_object_del(ad->webview);
		evas_object_del(ad->more_button);
	}
	eext_more_option_opened_set(obj, false);
}

static void
gl_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = (appdata_s *)data;
	Evas_Object *nf = ad->nf;
	Elm_Object_Item *nf_it;
	Elm_Object_Item *it = (Elm_Object_Item *)event_info;
	elm_object_item_text_get(it);
	item_data *id = elm_object_item_data_get(it);
	elm_genlist_item_selected_set(it, EINA_FALSE);

	ad->web_evas = evas_object_evas_get(ad->nf);
	ad->webview = ewk_view_add(ad->web_evas);
	ewk_view_url_set(ad->webview, main_menu_names[id->index][1]);
	evas_object_size_hint_weight_set(ad->webview, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(nf, ad->webview);
	eext_rotary_object_event_activated_set(ad->webview, EINA_TRUE);
	//evas_object_smart_callback_add(ad->webview, "close,window", naviframe_pop_cb_webview, ad);
	evas_object_show(ad->webview);

	ad->more_button = eext_more_option_add(ad->webview);
	Evas_Object *img = NULL;
	eext_more_option_direction_set(ad->more_button, EEXT_MORE_OPTION_DIRECTION_RIGHT);
	evas_object_move(ad->more_button, 180, 180);
    evas_object_size_hint_weight_set(ad->more_button, EVAS_HINT_FILL, EVAS_HINT_FILL);


	Eext_Object_Item *item  = eext_more_option_item_append(ad->more_button);
	eext_more_option_item_part_text_set(item, "selector,main_text", "Switch to");
	eext_more_option_item_part_text_set(item, "selector,sub_text", "WearableView");
	img = elm_image_add(ad->webview);
	eext_more_option_item_part_content_set(item, "item,icon", img);
	elm_image_file_set(img, ICON_DIR"/gear.png", NULL);

	item  = eext_more_option_item_append(ad->more_button);
	eext_more_option_item_part_text_set(item, "selector,main_text", "Go Back");
	img = elm_image_add(ad->nf);
	eext_more_option_item_part_content_set(item, "item,icon", img);
	elm_image_file_set(img, ICON_DIR"/goback.png", NULL);


	item  = eext_more_option_item_append(ad->more_button);
	eext_more_option_item_part_text_set(item, "selector,main_text", "Go Forward");
	img = elm_image_add(ad->webview);
	eext_more_option_item_part_content_set(item, "item,icon", img);
	elm_image_file_set(img, ICON_DIR"/goforward.png", NULL);

	item  = eext_more_option_item_append(ad->more_button);
	eext_more_option_item_part_text_set(item, "selector,main_text", "Show List");
	img = elm_image_add(ad->webview);
	eext_more_option_item_part_content_set(item, "item,icon", img);
	elm_image_file_set(img, ICON_DIR"/list.png", NULL);

	evas_object_smart_callback_add(ad->more_button, "item,clicked", _more_item_clicked, ad);

	evas_object_show(ad->more_button);


    nf_it = elm_naviframe_item_push(nf, "webview", NULL, NULL, ad->webview, "empty");
    elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb_webview, ad);


}

static char *
_gl_menu_title_text_get(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];

	snprintf(buf, 1023, "%s", "Top Websites");
	return strdup(buf);
}

static char *
_gl_menu_text_get(void *data, Evas_Object *obj, const char *part)
{
	char buf[1024];
	item_data *id = (item_data *)data;
	int index = id->index;

	if (!strcmp(part, "elm.text")) {
		snprintf(buf, 1023, "%s", main_menu_names[index][0]);
		return strdup(buf);
	}
	return NULL;
}

static void
_gl_menu_del(void *data, Evas_Object *obj)
{
	// FIXME: Unrealized callback can be called after this.
	// Accessing Item_Data can be dangerous on unrealized callback.
	item_data *id = (item_data *)data;
	if (id) free(id);
}

static void
_genlist_longpress_cb(void *data, Evas_Object *obj, void *event_info)
{

}
static void
create_list_view(appdata_s *ad,bool init)
{
	Evas_Object *circle_genlist;
	Evas_Object *genlist = ad->genlist;
	Evas_Object *nf = ad->nf;
	Elm_Object_Item *nf_it;
	Elm_Genlist_Item_Class *itc = elm_genlist_item_class_new();
	Elm_Genlist_Item_Class *ttc = elm_genlist_item_class_new();
	Elm_Genlist_Item_Class *ptc = elm_genlist_item_class_new();
	item_data *id;
	int index = 0;
	dlog_print(DLOG_INFO, "MyTag", "Creation of the genlist.");
	/* Genlist */
	genlist = elm_genlist_add(nf);
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);
	elm_genlist_homogeneous_set(genlist,true);
	elm_genlist_multi_select_set(genlist,true);
	elm_genlist_longpress_timeout_set(genlist, 1.0);
	elm_genlist_select_mode_set(genlist, ELM_OBJECT_SELECT_MODE_ALWAYS);
	evas_object_smart_callback_add(genlist, "selected", gl_selected_cb, ad);
	evas_object_smart_callback_add(genlist, "longpressed", _genlist_longpress_cb, ad);
	circle_genlist = eext_circle_object_genlist_add(genlist, ad->circle_surface);
	eext_circle_object_genlist_scroller_policy_set(circle_genlist, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	eext_rotary_object_event_activated_set(circle_genlist, EINA_TRUE);

	/* Genlist Title Item style */
	ttc->item_style = "title";
	ttc->func.text_get = _gl_menu_title_text_get;
	ttc->func.del = _gl_menu_del;

	/* Genlist Item style */
	itc->item_style = "default";
	itc->func.text_get = _gl_menu_text_get;
	itc->func.del = _gl_menu_del;

	/* Genlist Padding Item style */
	ptc->item_style = "padding";
	ptc->func.del = _gl_menu_del;

	/* Title Items Here */
	elm_genlist_item_append(genlist, ttc, NULL, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);

	/* Main Menu Items Here */
	for(int i=0;i<89;i++) {
		id = calloc(sizeof(item_data), 1);
		id->index = index++;
		id->item = elm_genlist_item_append(genlist, itc, id, NULL, ELM_GENLIST_ITEM_NONE, NULL, ad);
	}
	elm_genlist_item_append(genlist, ptc, NULL, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);

	elm_genlist_item_class_free(itc);
	elm_genlist_item_class_free(ttc);
	elm_genlist_item_class_free(ptc);

	/* This button is set for devices which doesn't have H/W back key. */

		nf_it = elm_naviframe_item_push(nf, NULL, NULL, NULL, genlist, "empty");
		elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb, ad->win);


}

static void
create_base_gui(appdata_s *ad)
{

	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Conformant */
	/* Create and initialize elm_conformant.
	   elm_conformant is mandatory for base gui to have proper size
	   when indicator or virtual keypad is visible. */
	ad->conform = elm_conformant_add(ad->win);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	// Eext Circle Surface Creation
	ad->circle_surface = eext_circle_surface_conformant_add(ad->conform);
	/* Base Layout */
	ad->layout = elm_layout_add(ad->conform);
	evas_object_size_hint_weight_set(ad->layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_layout_theme_set(ad->layout, "layout", "application", "default");
	evas_object_show(ad->layout);
	elm_object_content_set(ad->conform, ad->layout);

	ad->nf = elm_naviframe_add(ad->layout);

	create_list_view(ad,true);
	elm_object_part_content_set(ad->layout, "elm.swallow.content", ad->nf);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, NULL);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, eext_naviframe_more_cb, NULL);

	evas_object_show(ad->win);
}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;

	create_base_gui(ad);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}

#ifndef __basicui3_H__
#define __basicui3_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <ewk_view.h>
#include <ewk_context.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "tinybrowser"

#if !defined(PACKAGE)
#define PACKAGE "org.example.tinybrowser"
#endif

#define ICON_DIR "/opt/usr/apps/org.example.tinybrowser/res"

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
	Evas_Object *webview;
	Evas_Object *more_button;
	Evas_Object *circle_surface;
	Evas_Object *layout;
	Evas_Object *weblayout;
	Evas_Object *nf;
	Evas_Object *genlist;
	Evas *web_evas;
} appdata_s;

char *main_menu_names[][2] = {
{"NDTV","https://www.NDTV.com"},
{"indiatimes","https://www.indiatimes.com"},
{"BBC","https://www.BBC.com"},
{"Scroll","https://www.Scroll.in"},
{"asdf","https://www.asdf.com"},
{"news.google","https://www.news.google.com"},
{"wsj","https://www.wsj.com"},
{"indianexpress","https://www.indianexpress.com"},
{"newsweek","https://www.newsweek.com"},
{"Mathrubhumi","https://www.Mathrubhumi.com"},
{"Dowjones","https://www.Dowjones.com"},
{"stltoday","https://www.stltoday.com"},
{"nypost","https://www.nypost.com"},
{"Cbc.ca/news/","https://www.Cbc.ca/news/"},
{"washingtontimes","https://www.washingtontimes"},
{"news.yahoo","https://www.news.yahoo.com"},
{"washingtonexaminer","https://www.washingtonexaminer.com"},
{"washingtonpost","https://www.washingtonpost.com"},
{"Thehill","https://www.Thehill.com"},
{"Yr","https://www.Yr.no"},
{"Bostonglobe","https://www.Bostonglobe.com"},
{"Deccanchronicle","https://www.Deccanchronicle.com"},
{"Dnaindia","https://www.Dnaindia.com"},
{"Sacbee","https://www.Sacbee.com"},
{"Oregonlive","https://www.Oregonlive.com"},
{"chicagotribune","https://www.chicagotribune.com"},
{"cnbc","https://www.cnbc.com"},
{"Al","https://www.Al.com"},
{"Hindustantimes","https://www.Hindustantimes.com"},
{"Nbcnews","https://www.Nbcnews.com"},
{"Globaltimes.cn","https://www.Globaltimes.cn"},
{"Thestar","https://www.Thestar.com"},
{"Nj","https://www.Nj.com"},
{"Theglobeandmail","https://www.Theglobeandmail.com"},
{"Startribune","https://www.Startribune.com"},
{"Dallasnews","https://www.Dallasnews.com"},
{"Ajc","https://www.Ajc.com"},
{"Weather","https://www.Weather.com"},
{"Hollywoodreporter","https://www.Hollywoodreporter.com"},
{"chron","https://www.chron.com"},
{"heraldsun","https://www.heraldsun.com.au"},
{"Azcentral","https://www.Azcentral.com"},
{"Usatoday","https://www.Usatoday.com"},
{"Theatlantic","https://www.Theatlantic.com"},
{"Thehindu","https://www.Thehindu"},
{"Theguardian","https://www.Theguardian.com"},
{"reddit","https://www.reddit.com"},
{"Financialexpress","https://www.Financialexpress.com"},
{"variety","https://www.variety.com"},
{"Indiatimes","https://www.Indiatimes.com"},
{"Nytimes","https://www.Nytimes.com"},
{"Business-standard","https://www.Business-standard.com"},
{"Philly","https://www.Philly.com"},
{"Forbes","https://www.Forbes.com"},
{"Cbsnews","https://www.Cbsnews.com"},
{"Latimes","https://www.Latimes.com"},
{"Wunderground","https://www.Wunderground.com"},
{"Abcnews.go","https://www.Abcnews.go.com"},
{"Reuters","https://www.Reuters.com"},
{"Bloomberg","https://www.Bloomberg.com"},
{"Thedailybeast","https://www.Thedailybeast.com"},
{"Denverpost","https://www.Denverpost.com"},
{"Cnn","https://www.Cnn.com"},
{"Foxnews","https://www.Foxnews.com"},
{"Drudgereport","https://www.Drudgereport.com"},
{"Timesofindia","https://www.Timesofindia.indiatimes.com"},
{"Dw","https://www.Dw.com"},
{"Sfgate","https://www.Sfgate.com"},
{"Seattletimes","https://www.Seattletimes.com"},
{"Weather.gov","https://www.Weather.gov"},
{"Theage","https://www.Theage.com.au"},
{"News","https://www.News.com.au"},
{"Nationalgeographic","https://www.Nationalgeographic.com"},
{"Time","https://www.Time.com"},
{"Smh","https://www.Smh.com.au"},
{"Usnews","https://www.Usnews.com"},
{"Mercurynews","https://www.Mercurynews.com"},
{"Livemint","https://www.Livemint.com"},
{"Nationalpost","https://www.Nationalpost.com"},
{"Economictimes","https://www.Economictimes.indiatimes.com"},
{"Baltimoresun","https://www.Baltimoresun.com"},
{"Huffingtonpost","https://www.Huffingtonpost.com"},
{"Chinadaily.cn","https://www.Chinadaily.com.cn"},
{"Bbc.co.uk/news/","https://www.Bbc.co.uk/news/"},
{"Maimiherald","https://www.Maimiherald.com"},
{"Shutterstock","https://www.Shutterstock.com"},
{"Accuweather","https://www.Accuweather.com"},
{"Money.cnn","https://www.Money.cnn.com"},
{"Theepochtimes","https://www.Theepochtimes.com"}
};
static void create_list_view(appdata_s *ad,bool );
#endif /* __basicui3_H__ */

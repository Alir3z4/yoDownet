/****************************************************************************************
** languages.cpp is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "languages.h"

QMap<QString, QString> Languages::translations()
{
    QMap<QString, QString> m;

//    m["aa"] = tr("Afar");
//    m["ab"] = tr("Abkhazian");
//    m["ae"] = tr("Avestan");
//    m["af"] = tr("Afrikaans");
//    m["ak"] = tr("Akan");
//    m["am"] = tr("Amharic");
//    m["an"] = tr("Aragonese");
//    m["ar"] = tr("Arabic");
//    m["as"] = tr("Assamese");
//    m["av"] = tr("Avaric");
//    m["ay"] = tr("Aymara");
//    m["az"] = tr("Azerbaijani");
//    m["ba"] = tr("Bashkir");
//    m["be"] = tr("Belarusian");
//    m["bg"] = tr("Bulgarian");
//    m["bh"] = tr("Bihari");
//    m["bi"] = tr("Bislama");
//    m["bm"] = tr("Bambara");
//    m["bn"] = tr("Bengali");
//    m["bo"] = tr("Tibetan");
//    m["br"] = tr("Breton");
//    m["bs"] = tr("Bosnian");
//    m["ca"] = tr("Catalan");
//    m["ce"] = tr("Chechen");
//    m["co"] = tr("Corsican");
//    m["cr"] = tr("Cree");
    m["cs"] = tr("Czech");
//    m["cu"] = tr("Church");
//    m["cv"] = tr("Chuvash");
//    m["cy"] = tr("Welsh");
//    m["da"] = tr("Danish");
//    m["de"] = tr("German");
//    m["dv"] = tr("Divehi");
//    m["dz"] = tr("Dzongkha");
//    m["ee"] = tr("Ewe");
//    m["el"] = tr("Greek");
    m["en"] = tr("English");
//    m["eo"] = tr("Esperanto");
//    m["es"] = tr("Spanish");
    m["et"] = tr("Estonian");
//    m["eu"] = tr("Basque");
    m["fa"] = tr("Persian");
//    m["ff"] = tr("Fulah");
//    m["fi"] = tr("Finnish");
//    m["fj"] = tr("Fijian");
//    m["fo"] = tr("Faroese");
//    m["fr"] = tr("French");
//    m["fy"] = tr("Frisian");
//    m["ga"] = tr("Irish");
//    m["gd"] = tr("Gaelic");
//    m["gl"] = tr("Galician");
//    m["gn"] = tr("Guarani");
//    m["gu"] = tr("Gujarati");
//    m["gv"] = tr("Manx");
//    m["ha"] = tr("Hausa");
//    m["he"] = tr("Hebrew");
//    m["hi"] = tr("Hindi");
//    m["ho"] = tr("Hiri");
//    m["hr"] = tr("Croatian");
//    m["ht"] = tr("Haitian");
//    m["hu"] = tr("Hungarian");
//    m["hy"] = tr("Armenian");
//    m["hz"] = tr("Herero");
//    m["ch"] = tr("Chamorro");
//    m["ia"] = tr("Interlingua");
//    m["id"] = tr("Indonesian");
//    m["ie"] = tr("Interlingue");
//    m["ig"] = tr("Igbo");
//    m["ii"] = tr("Sichuan");
//    m["ik"] = tr("Inupiaq");
//    m["io"] = tr("Ido");
//    m["is"] = tr("Icelandic");
//    m["it"] = tr("Italian");
//    m["iu"] = tr("Inuktitut");
//    m["ja"] = tr("Japanese");
//    m["jv"] = tr("Javanese");
//    m["ka"] = tr("Georgian");
//    m["kg"] = tr("Kongo");
//    m["ki"] = tr("Kikuyu");
//    m["kj"] = tr("Kuanyama");
//    m["kk"] = tr("Kazakh");
//    m["kl"] = tr("Greenlandic");
//    m["km"] = tr("Khmer");
//    m["kn"] = tr("Kannada");
//    m["ko"] = tr("Korean");
//    m["kr"] = tr("Kanuri");
//    m["ks"] = tr("Kashmiri");
//    m["ku"] = tr("Kurdish");
//    m["kv"] = tr("Komi");
//    m["kw"] = tr("Cornish");
//    m["ky"] = tr("Kirghiz");
//    m["la"] = tr("Latin");
//    m["lb"] = tr("Luxembourgish");
//    m["lg"] = tr("Ganda");
//    m["li"] = tr("Limburgan");
//    m["ln"] = tr("Lingala");
//    m["lo"] = tr("Lao");
//    m["lt"] = tr("Lithuanian");
//    m["lu"] = tr("Luba-Katanga");
//    m["lv"] = tr("Latvian");
//    m["mg"] = tr("Malagasy");
//    m["mh"] = tr("Marshallese");
//    m["mi"] = tr("Maori");
//    m["mk"] = tr("Macedonian");
//    m["ml"] = tr("Malayalam");
//    m["mn"] = tr("Mongolian");
//    m["mo"] = tr("Moldavian");
//    m["mr"] = tr("Marathi");
//    m["ms"] = tr("Malay");
//    m["mt"] = tr("Maltese");
//    m["my"] = tr("Burmese");
//    m["na"] = tr("Nauru");
//    m["nb"] = trUtf8("Bokmål");
//    m["nd"] = tr("Ndebele");
//    m["ne"] = tr("Nepali");
//    m["ng"] = tr("Ndonga");
    m["nl"] = tr("Dutch");
//    m["nn"] = tr("Norwegian");
//    m["no"] = tr("Norwegian");
//    m["nr"] = tr("Ndebele");
//    m["nv"] = tr("Navajo");
//    m["ny"] = tr("Chichewa");
//    m["oc"] = tr("Occitan");
//    m["oj"] = tr("Ojibwa");
//    m["om"] = tr("Oromo");
//    m["or"] = tr("Oriya");
//    m["os"] = tr("Ossetian");
//    m["pa"] = tr("Panjabi");
//    m["pi"] = tr("Pali");
//    m["pl"] = tr("Polish");
//    m["ps"] = tr("Pushto");
//    m["pt"] = tr("Portuguese");
//    m["qu"] = tr("Quechua");
//    m["rm"] = tr("Romansh");
//    m["rn"] = tr("Rundi");
//    m["ro"] = tr("Romanian");
//    m["ru"] = tr("Russian");
//    m["rw"] = tr("Kinyarwanda");
//    m["sa"] = tr("Sanskrit");
//    m["sc"] = tr("Sardinian");
//    m["sd"] = tr("Sindhi");
//    m["se"] = tr("Sami");
//    m["sg"] = tr("Sango");
//    m["si"] = tr("Sinhala");
//    m["sk"] = tr("Slovak");
//    m["sl"] = tr("Slovenian");
//    m["sm"] = tr("Samoan");
//    m["sn"] = tr("Shona");
//    m["so"] = tr("Somali");
//    m["sq"] = tr("Albanian");
//    m["sr"] = tr("Serbian");
//    m["ss"] = tr("Swati");
//    m["st"] = tr("Sotho");
//    m["su"] = tr("Sundanese");
//    m["sv"] = tr("Swedish");
//    m["sw"] = tr("Swahili");
//    m["ta"] = tr("Tamil");
//    m["te"] = tr("Telugu");
//    m["tg"] = tr("Tajik");
//    m["th"] = tr("Thai");
//    m["ti"] = tr("Tigrinya");
//    m["tk"] = tr("Turkmen");
//    m["tl"] = tr("Tagalog");
//    m["tn"] = tr("Tswana");
//    m["to"] = tr("Tonga");
    m["tr"] = tr("Turkish");
//    m["ts"] = tr("Tsonga");
//    m["tt"] = tr("Tatar");
//    m["tw"] = tr("Twi");
//    m["ty"] = tr("Tahitian");
//    m["ug"] = tr("Uighur");
//    m["uk"] = tr("Ukrainian");
//    m["ur"] = tr("Urdu");
//    m["uz"] = tr("Uzbek");
//    m["ve"] = tr("Venda");
    m["vi"] = tr("Vietnamese");
//    m["vo"] = trUtf8("Volapük");
//    m["wa"] = tr("Walloon");
//    m["wo"] = tr("Wolof");
//    m["xh"] = tr("Xhosa");
//    m["yi"] = tr("Yiddish");
//    m["yo"] = tr("Yoruba");
//    m["za"] = tr("Zhuang");
//    m["zh"] = tr("Chinese");
//    m["zu"] = tr("Zulu");

    return m;
}

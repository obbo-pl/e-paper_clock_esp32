/*
 * lang.h
 *
 * Created on: 14 sty 2022
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * This program is distributed under the terms of the GNU General Public License
 */

#ifndef _LANG_H_
#define _LANG_H_



#if defined(CONFIG_EPCLOCK_LANG_de_DE)
	const char *day_abbr[7] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
	const char *day_name[7] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
	const char *month_abbr[12] = {"Jan", "Feb", "Mär", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};
	const char *month_name[12] = {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
#elif defined(CONFIG_EPCLOCK_LANG_es_ES)
	const char *day_abbr[7] = {"dom", "lun", "mar", "mié", "jue", "vie", "sáb"};
	const char *day_name[7] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
	const char *month_abbr[12] = {"ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};
	const char *month_name[12] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
#elif defined(CONFIG_EPCLOCK_LANG_fr_FR)
	const char *day_abbr[7] = {"dim.", "lun.", "mar.", "mer.", "jeu.", "ven.", "sam."};
	const char *day_name[7] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
	const char *month_abbr[12] = {"janv.", "févr.", "mars", "avril", "mai", "juin", "juil.", "août", "sept", "oct.", "nov.", "déc."};
	const char *month_name[12] = {"janvier", "février", "mars", "avril", "mai", "juin", "juillet", "août", "septembre", "octobre", "novembre", "décembre"};
#elif defined(CONFIG_EPCLOCK_LANG_pl_PL)
	const char *day_abbr[7] = {"nie", "pon", "wto", "śro", "czw", "pią", "sob"};
	const char *day_name[7] = {"niedziela", "poniedziałek", "wtorek", "środa", "czwartek", "piątek", "sobota"};
	const char *month_abbr[12] = {"sty", "lut", "mar", "kwi", "maj", "cze", "lip", "sie", "wrz", "paź", "lis", "gru"};
	const char *month_name[12] = {"styczeń", "luty", "marzec", "kwiecień", "maj", "czerwiec", "lipiec", "sierpień", "wrzesień", "październik", "listopad", "grudzień"};
#else
	// default EPCLOCK_LANG_en_GB | EPCLOCK_LANG_en_US
	const char *day_abbr[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	const char *day_name[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	const char *month_abbr[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	const char *month_name[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
#endif



#endif /* _LANG_H_ */

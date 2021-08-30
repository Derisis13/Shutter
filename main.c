#include "idozites.h"
#include "mozgatas_demo.h"
#include <stdio.h>
#define FILEPATH "menetrend.txt"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * REDŐNY AUTOMATA
 * ---------------
 * C program az itthoni redőnyök automatizálására egy kiszuperált router és egy kompatibilis távirányító segítségével.
 * A programot egy időzítő (Cron) hívja meg fix időközönként.
 * Egy helyi fájlból, a menetrend.txt-ből olvassa ki a felhúzások és lehúzások idejét, ha annyi az idő, fel/lehúzza,
 * ez egy heti menetrendet képes tárolni és végrehajtani.
 * GPIO-kkal vezérli a távirányító gombmátrixát.
 * A programot OpenWrt 19.07-re fordítom. HW: D-Link DIR-600. (fordítási környezethez:$ source openwrt.config)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main ()
{
  redony ercsi13[] = {
      {
          1, 0, 0 //fiúszoba
      },
      {
          2, 0, 0 //lányszoba
      },
      {
          3, 0, 0 //nappali bal
      },
      {
          4, 0, 0 //nappali jobb
      },
      {
          5, 0, 0 //szülői szoba
      },
      {
          6, 0, 0 //konyha
      },
      {
          7, 0, 0 //előtető (lehúzás = kieresztés, felhúzás = behúzás)
      }
  };

  //beolvassuk minden redőny időpontját
  for (int i = 0; i < 7; ++i)
    {
      FILE *schedule = fopen (FILEPATH, "r");
      find_today (schedule);
      get_timing (&ercsi13[i], schedule);
      fclose (schedule);
    }

  /*
  //exportáljuk a gpio-kat, hogy tudjuk használni őket
  export ();
  */

  //leellenőrizzük az időpontokat, minden redőny úgy mozog, ahhogy azt megmondtuk neki.
  for (int i = 0; i < 7; ++i)
    {
      set_ch (&ercsi13[i]);
      press_button (check_timing (&ercsi13[i]));
    }
  return 0;
}
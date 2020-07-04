/*#include <ctime>
#include <iostream>
using namespace std;

int main() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    string date;
    day=
    cout<<date;
    cout << (now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-'  <<  (now->tm_mday)
         << endl;
}*/


#include <iostream>
#include <ctime>
using namespace std;
int main ()
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%d-%m-%Y",timeinfo);
  string date(buffer);

  cout << date;

  return 0;
}

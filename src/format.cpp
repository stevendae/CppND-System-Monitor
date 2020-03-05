#include <string>
#include <math.h>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long total) {
    float time, hours, minutes, seconds;
    time = total / 3600.0;

    minutes = modf(time, &hours);

    time = minutes * 60;

    seconds = modf(time, &minutes);

    time = seconds * 60;

    modf(time, &seconds);
    int h = static_cast<int>(hours);
    int m = static_cast<int>(minutes);
    int s = static_cast<int>(seconds);

    string h_, m_, s_;
    if (h <10) {
        h_ = "0"+std::to_string(h);
    }
    else {h_ = std::to_string(h);}

    if (m <10) {
        m_ = "0"+std::to_string(m);
    }
    else {m_ = std::to_string(m);}

    if (s <10) {
        s_ = "0"+std::to_string(s);
    }
    else {s_ = std::to_string(s);}

    return string (h_+":"+m_+":"+s_);



}
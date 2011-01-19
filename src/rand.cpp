/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <cstdlib>
#include "rand.h"

double randomNumber() {
    return rand() / RAND_MAX;
}

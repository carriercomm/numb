/***************************************************************************
                          memory.h  -  description
                             -------------------
    begin                : Ven nov 8 2002
    copyright            : (C) 2002 by spe
    email                : spe@artik.intra.selectbourse.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MEMORY_H
#define MEMORY_H

#include <errno.h>
#include "log.h"
#include "debugtk.h"

extern LogError *systemLog;

/**This is a baseclass for managing memory blocks.
  *@author spe
  */

template<class Item> class Memory {
protected:
  int blocSize;
  int elementSize;
  int numberOfElements;
public: 
  Item *bloc;
  
  Memory(int);
  ~Memory();
  int getBlocSize(void) { return blocSize; };
  Item *getBloc(void) { return bloc; };
};

template<class Item> Memory<Item>::Memory(int _numberOfElements) {
  register int itemSize = sizeof(Item);

  // Remplacer les callocs par NEW char
  bloc = (Item *)calloc(_numberOfElements, itemSize);
  if (! bloc) {
    systemLog->sysLog(LOG_CRIT, "*** Warning *** cannot allocate memory: %s\n", strerror(errno));
    blocSize = 0;
    bloc = NULL;
    return;
  }
  elementSize = itemSize;
  numberOfElements = _numberOfElements;
  blocSize = numberOfElements * elementSize;
  bzero(bloc, blocSize);

  return;
}

template<class Item> Memory<Item>::~Memory() {
  bzero(bloc, blocSize);
  free(bloc);
  bloc = NULL;
}

#endif

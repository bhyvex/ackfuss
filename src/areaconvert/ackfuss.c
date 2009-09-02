/*
 * Copyright Matt Goff (Kline) 2009
 * If you use my code, please give credit where it is due.
 * Support provided at www.ackmud.net
 */

#include "h/areaconvert.h"
#include "h/extern.h"

void write_ackfuss( ofstream &file, int type )
{
 write_ackfuss_area(file,type);
 write_ackfuss_room(file,type);

 file << "#$" << endl; /* the end */

 return;
}

void write_ackfuss_area( ofstream &file, int type )
{
 char delim = '~';
 int i = 0;

 file << "#AREA" << endl;
 file << "Revision  " << area.revision << endl;
 file << "CanRead  " << area.can_read << delim << endl;
 file << "CanWrite " << area.can_write << delim << endl;
 file << "Flags     ";
 for( i = 0; i < MAX_BITSET; i++ )
  if( area.bitset_flags_out.test(i) )
   file << i << " ";
 file << "EOL" << endl;
 file << "Keyword  " << area.keyword << delim << endl;
 file << "LevLabel " << area.level_label << delim << endl;
 file << "LevRange  " << area.min_level << " " << area.max_level << endl;
 file << "Name      " << area.name << delim << endl;
 file << "Owner    " << area.owner << delim << endl;
 file << "ResetMsg " << area.reset_msg << delim << endl;
 file << "ResetRate " << area.reset_rate << endl;
 file << "VnumRange " << area.min_vnum << " " << area.max_vnum << endl;
 file << "End" << endl;

 return;
}

void write_ackfuss_room( ofstream &file, int type )
{
 char delim = '~';
 list<room_data *>::iterator rt;
 list<extra_data *>::iterator et;
 room_data *room;
 extra_data *extra;
 int i = 0, x = 0;

 for( rt = room_list.begin(); rt != room_list.end(); rt++ )
 {
  room = *rt;
  file << "#ROOM" << endl;
  file << "Vnum    " << room->vnum << endl;
  file << "Desc    " << room->description << delim << endl;
  file << "Flags   ";
  for( i = 0; i < MAX_BITSET; i++ )
   if( room->bitset_flags_out.test(i) )
    file << i << " ";
  file << "EOL" << endl;
  file << "Name    " << room->name << delim << endl;
  file << "Sect    " << room->sector << endl;
  file << "End" << endl;

  for( i = 0; i < MAX_EXIT; i++ )
  {
   if( room->exit[i] )
   {
    file << "#DOOR" << endl;
    file << "Dir     " << i << endl; /* Must be first for sanity checks --Kline */
    file << "Desc    " << room->exit[i]->description << delim << endl;
    file << "Flags   ";
    for( x = 0; x < MAX_BITSET; x++ )
     if( room->exit[i]->bitset_flags_out.test(x) )
      file << x << " ";
    file << "EOL" << endl;
    file << "Key     " << room->exit[i]->key << endl;
    file << "Keyword " << room->exit[i]->keyword << delim << endl;
    file << "Vnum    " << room->exit[i]->vnum << endl;
    file << "End" << endl;
   }
  }

  for( et = room->extra_list.begin(); et != room->extra_list.end(); et++ )
  {
   extra = *et;
   file << "#REXTRA" << endl;
   file << "Desc     " << extra->description << delim << endl;
   file << "Keyword  " << extra->keyword << delim << endl;
   file << "End" << endl;
  }
 }

 return;
}

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
#include<cstdint>

using namespace std;

//There are 18 message types

class timeStamp{
public:
char message; //Of type 'T'
uint32_t second; //Number of seconds since midnight
void print()
  {
    cout<<endl<<message<<" "<<second;
  }
void convert_endian()
 {
   second = __builtin_bswap32(second);
 }
}__attribute__((packed));
class systemEventMessage{
public:
char message; //Of type 'S'
uint32_t timeStamp; //nanosecond portion of time stamp
char eventCode;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<eventCode;
  }
void convert_endian()
{
  timeStamp = __builtin_bswap32(timeStamp);
}

}__attribute__((packed));
class stockDirectory{
public:
char message; //Of type 'R'
uint32_t timeStamp;//nanosecond portion of the time stamp
char stock[8];
char marketCategory;
char financialStatusIndicator;
uint32_t roundLotSize;
char roundLotsOnly;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "
    <<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7]
    <<" "<<marketCategory<<" "<<financialStatusIndicator<<" "<<roundLotSize<<" "<<roundLotsOnly;
  }

void convert_endian()
{
  timeStamp = __builtin_bswap32(timeStamp);
  roundLotSize = __builtin_bswap32(roundLotSize);
}
}__attribute__((packed));
class stockTradingAction{
public:
char message;//of type 'H'
uint32_t timeStamp;
char stock[8];
char tradingState;
char reserved;
char reason[4];
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
  }
void convert_endian()
 {
  timeStamp = __builtin_bswap32(timeStamp);
 }
}__attribute__((packed));
class regShoRestriction{
public:
char message;//of type 'Y'
uint32_t timeStamp;
char stock[8];
char regShoAction;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
  }
void convert_endian()
  {
    timeStamp = __builtin_bswap32(timeStamp);
  }
}__attribute__((packed));

class marketParticipantPosition{
public:
char message;//of type 'L'
uint32_t timeStamp;
char mpid[4];
char stock[8];
char primaryMarketMaker;
char marketMakerMode;
char marketParticipantState;

void convert_endian()
{
  timeStamp = __builtin_bswap32(timeStamp);
}

void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
  }

}__attribute__((packed));

class addOrderMessage{
public:
char message;//of type 'A'
uint32_t timeStamp;
uint64_t OID;
char buySellIndicator;
uint32_t shares;
char stock[8];
uint32_t price;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
    cout<<" "<<price<<" "<<OID<<" "<<shares<<" "<<buySellIndicator;
  }
void convert_endian()
  {
    timeStamp = __builtin_bswap32(timeStamp);
    OID = __builtin_bswap64(OID);
    shares = __builtin_bswap32(shares);
    price = __builtin_bswap32(price);
  }

}__attribute__((packed));

class addOrderMessageAttribution{
public:
char message;//of type 'F'
uint32_t timeStamp;
uint64_t OID;
char buySellIndicator;
uint32_t shares;
char stock[8];
uint32_t price;
char attribution[4];
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
    cout<<" "<<price<<" "<<OID<<" "<<shares<<" "<<buySellIndicator;
  }
void convert_endian()
 {
   timeStamp = __builtin_bswap32(timeStamp);
   OID = __builtin_bswap64(OID);
   shares = __builtin_bswap32(shares);
   price = __builtin_bswap32(price);
 }

}__attribute__((packed));

class orderExecutedMessage{
public:
char message;//of type 'E'
uint32_t timeStamp;
uint64_t OID;
uint32_t executedShares;
uint64_t matchNumber;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<OID<<" "<<executedShares<<" "<<matchNumber;
  }
void convert_endian()
  {
    timeStamp = __builtin_bswap32(timeStamp);
    OID = __builtin_bswap64(OID);
    executedShares = __builtin_bswap32(executedShares);
    matchNumber = __builtin_bswap64(matchNumber);
  }
}__attribute__((packed));

class orderExecutedWithPriceMessage{
public:
char message;//of type 'C'
uint32_t timeStamp;
uint64_t OID;
uint32_t executedShares;
uint64_t matchNumber;
char printable;
uint32_t executionPrice;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<OID<<" "<<executedShares<<" "<<matchNumber<<" "<<printable<<" "<<executionPrice;
  }
void convert_endian()
  {
     timeStamp = __builtin_bswap32(timeStamp);
     OID = __builtin_bswap64(OID);
     executedShares = __builtin_bswap32(executedShares);
     matchNumber = __builtin_bswap64(matchNumber);
     executionPrice = __builtin_bswap32(executionPrice);  
  }

}__attribute__((packed));

class orderCancelMessage{
public:
char message;//of type 'X'
uint32_t timeStamp;
uint64_t OID;
uint32_t canceledShares;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<OID<<" "<<canceledShares;
  }
void convert_endian()
  { 
    timeStamp = __builtin_bswap32(timeStamp);  OID = __builtin_bswap64(OID);
    canceledShares = __builtin_bswap32(canceledShares);
  }
}__attribute__((packed));

class orderDeleteMessage{
public:
char message;//of type 'D'
uint32_t timeStamp;
uint64_t OID;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<OID;
  }
void convert_endian()
  {
    timeStamp = __builtin_bswap32(timeStamp);
    OID = __builtin_bswap64(OID);
  }
}__attribute__((packed));

class orderReplaceMessage{
public:
char message;//of type 'U'
uint32_t timeStamp;
uint64_t originalOID;
uint64_t newOID;
uint32_t shares;
uint32_t price;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<originalOID<<" "<<newOID;
  }
void convert_endian()
{
  timeStamp = __builtin_bswap32(timeStamp);
  originalOID = __builtin_bswap64(originalOID);
  newOID = __builtin_bswap64(newOID);
  shares = __builtin_bswap32(shares);
  price = __builtin_bswap32(price);
}
}__attribute__((packed));

class tradeMessageNonCross{
public:
char message;//of type 'P'
uint32_t timeStamp;
uint64_t OID;
char buySellIndicator;
uint32_t shares;
char stock[8];
uint32_t price;
uint64_t matchNumber;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
  }
void convert_endian()
  {
    timeStamp = __builtin_bswap32(timeStamp);    shares = __builtin_bswap32(shares); 
    OID = __builtin_bswap64(OID);                price = __builtin_bswap32(price); 
    matchNumber = __builtin_bswap64(matchNumber);
  }
}__attribute__((packed));

class tradeMessageCross{
public:
char message;//of type 'Q'
uint32_t timeStamp;
uint64_t shares;
uint64_t OID;
char stock[8];
uint32_t crossPrice;
uint64_t matchNumber;
char crossType;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
  }
void convert_endian()
  {
    timeStamp = __builtin_bswap32(timeStamp);    shares = __builtin_bswap64(shares); 
    OID = __builtin_bswap64(OID);                crossPrice = __builtin_bswap32(crossPrice); 
    matchNumber = __builtin_bswap64(matchNumber);
    
  }

}__attribute__((packed));

class brokenTrade{
public:
char message;//of type 'B'
uint32_t timeStamp;
uint64_t matchNumber;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<matchNumber;
  }
void convert_endian()
  { 
    timeStamp = __builtin_bswap32(timeStamp);
    matchNumber = __builtin_bswap64(matchNumber);
  }

}__attribute__((packed));

class netOrderImbalanceIndicator{
public:
char message;//of type 'I'
uint32_t timeStamp;
uint64_t pairedShares;
uint64_t imbalanceShares;
char imbalanceDirection;
char stock[8];
uint32_t fairPrice;
uint32_t nearPrice;
uint32_t currentReferencePrice;
char crossType;
char priceVariationIndicator;
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
  }
void convert_endian()
  {
    timeStamp = __builtin_bswap32(timeStamp);              pairedShares = __builtin_bswap32(pairedShares); 
    imbalanceShares = __builtin_bswap32(imbalanceShares);  fairPrice = __builtin_bswap32(fairPrice); 
    nearPrice = __builtin_bswap32(nearPrice);              currentReferencePrice = __builtin_bswap32(currentReferencePrice);
  }
}__attribute__((packed));

class retailPriceImprovementIndicator{
public:
char message; //of type 'N'
uint32_t timeStamp;
char stock[8];
char interestFlag[1];
void print()
  {
    cout<<endl<<message<<" "<<timeStamp<<" "<<stock[0]<<stock[1]<<stock[2]<<stock[3]<<stock[4]<<stock[5]<<stock[6]<<stock[7];
  }

void convert_endian()
 {
  timeStamp = __builtin_bswap32(timeStamp);
 }
}__attribute__((packed));


class order
{
public:
uint64_t OID;
uint32_t price;
uint32_t shares;
char side;
uint32_t nanoSecond;
uint32_t second;
void initialize(uint64_t o, uint32_t p, uint32_t s, char a_side, uint32_t sec, uint32_t ns)
{
  OID = o; price = p; shares = s; side = a_side; nanoSecond = ns; second = sec;
}
};

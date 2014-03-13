#include "book_routines.h"
using namespace std;

int main()
{
 fstream input_file;
 timeStamp o_timeStamp;
 systemEventMessage o_systemEventMessage;
 stockDirectory o_stockDirectory;
 stockTradingAction o_stockTradingAction;
 regShoRestriction o_regShoRestriction;
 marketParticipantPosition o_marketParticipantPosition;
 addOrderMessage o_addOrderMessage;
 addOrderMessageAttribution o_addOrderMessageAttribution;
 orderExecutedMessage o_orderExecutedMessage;
 orderExecutedWithPriceMessage o_orderExecutedWithPriceMessage;
 orderCancelMessage o_orderCancelMessage;
 orderDeleteMessage o_orderDeleteMessage;
 orderReplaceMessage o_orderReplaceMessage;
 tradeMessageNonCross o_tradeMessageNonCross;
 tradeMessageCross o_tradeMessageCross;
 brokenTrade o_brokenTrade;
 netOrderImbalanceIndicator o_netOrderImbalanceIndicator;
 retailPriceImprovementIndicator o_retailPriceImprovementIndicator;


 bool debugMode = 0;

 map<uint64_t, order> orderID_to_properties;
 map<uint32_t, map<uint64_t, order> > bidBook;
 map<uint32_t, map<uint64_t, order> > askBook;
 input_file.open("AAPL",ios::in | ios::binary);
 uint32_t lastTimeStamp;
 if(input_file ==  NULL)
   {
     exit(1);
   }
  else
   {  
     bool end_of_day = 0;
     bool start_of_trading = 0;
     
     while(!end_of_day )
      {
       char typeOfMessage;
       input_file.read((char*)&typeOfMessage,1);
      
       switch(typeOfMessage)
        {
           case 'T': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_timeStamp,sizeof(timeStamp));
                     o_timeStamp.print();
                     lastTimeStamp = o_timeStamp.second;
                     end_of_day  = (o_timeStamp.second == 57600);
                     start_of_trading = (o_timeStamp.second == 39600 || (start_of_trading == 1));
                     if(start_of_trading)
                     {
                      cout<<endl<<o_timeStamp.second<<" "<<bidBook.rbegin()->first<<" "<<askBook.begin()->first;
                      cin.get();
                     }
                     
                     break;
           case 'S': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_systemEventMessage,sizeof(systemEventMessage));
                     break;
           case 'R': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_stockDirectory,sizeof(stockDirectory));
                     break;
           case 'H': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_stockTradingAction,sizeof(stockTradingAction));
                     break;
           case 'Y': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_regShoRestriction,sizeof(regShoRestriction));
                     break;
           case 'L': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_marketParticipantPosition,sizeof(marketParticipantPosition));
                     break;
           case 'A': {
                     input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_addOrderMessage,sizeof(addOrderMessage));
                     order tempOrder;
                     tempOrder.initialize(o_addOrderMessage.OID, o_addOrderMessage.price, 
                                          o_addOrderMessage.shares, o_addOrderMessage.buySellIndicator);
                     orderID_to_properties.insert(pair<uint64_t,order>
                          (static_cast<uint64_t>(o_addOrderMessage.OID), tempOrder));
                     o_addOrderMessage.print();
                     /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"Before insert:-----------------------------------------"<<o_timeStamp.second;
                           o_addOrderMessage.print();
                           //print_order_book(bidBook, askBook);
                        }*/
                     bool uncross = 0;
                     if(tempOrder.shares >0) 
      						 {
                           uncross = add_order_book_entry(tempOrder,bidBook,askBook, 'A');
								 }
                     cout<<" "<<uncross;
                    /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"After insert:----------------------------------------Uncross="<<uncross;
                           //print_order_book(bidBook, askBook);
                           //cin.get();
                         }*/
                     }
                     break;
           case 'F': {
                     input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_addOrderMessageAttribution,sizeof(addOrderMessageAttribution));
							order tempOrder;
                     tempOrder.initialize(o_addOrderMessageAttribution.OID, o_addOrderMessageAttribution.price, 
                                          o_addOrderMessageAttribution.shares, o_addOrderMessageAttribution.buySellIndicator);
                     orderID_to_properties.insert(pair<uint64_t,order>
                          (static_cast<uint64_t>(o_addOrderMessageAttribution.OID), tempOrder));
          				o_addOrderMessageAttribution.print();
                       /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"Before insert:-----------------------------------------"<<o_timeStamp.second;
     								o_addOrderMessageAttribution.print();
                           //print_order_book(bidBook, askBook);                     
 						       }*/
 							bool uncross = 0;
                     if(tempOrder.shares > 0) uncross = add_order_book_entry(tempOrder,bidBook,askBook, 'F');
                     /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"After insert:--------------------------------------------Uncross="<<uncross;
                           //print_order_book(bidBook, askBook);
                           //cin.get();
                         }*/
                     
                     break;
							}
           case 'E': {
                     input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderExecutedMessage,sizeof(orderExecutedMessage));
                     map<uint64_t, order>::iterator it;
                     it = orderID_to_properties.find(static_cast<uint64_t>(o_orderExecutedMessage.OID)); 
                    o_orderExecutedMessage.print();
                     /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"Before execution:------------------------------------------------------------";
     								o_orderExecutedMessage.print();
                           //print_order_book(bidBook, askBook);                     
                         }*/
                      if(it == orderID_to_properties.end())
                        {
                           //cout<<endl<<"Executing an order not in the OID map!!";
                        }
                      else
                        {

  									order tempOrder = it->second; //Order that is getting executed
									execute_order_book_entry(tempOrder, o_orderExecutedMessage.executedShares, bidBook, askBook);
                        }
                     /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"After execution:------------------------------------------------------------";
                           //print_order_book(bidBook, askBook);                     
 							 		//cin.get();
                         }*/
                      
                     ////print_order_book(bidBook, askBook); 
                     }
                     break;
           case 'C': {
                     input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderExecutedWithPriceMessage,sizeof(orderExecutedWithPriceMessage));
                     map<uint64_t, order>::iterator it;
                     it = orderID_to_properties.find(static_cast<uint64_t>(o_orderExecutedWithPriceMessage.OID)); 
                     o_orderExecutedWithPriceMessage.print();
                     /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                        {
									cout<<endl<<"Before execution:------------------------------------------------------------";
     						 		o_orderExecutedWithPriceMessage.print();
                           //print_order_book(bidBook, askBook);                     
 									
                        }*/
                      if(it == orderID_to_properties.end()&& debugMode == 1)
                        {
                           //cout<<endl<<"Executing an order not in the OID map!!";
                        }
                      else
                        {
  									order tempOrder = it->second; //Order that is getting executed
									execute_order_book_entry(tempOrder, o_orderExecutedWithPriceMessage.executedShares, bidBook, askBook);
                        }
                       /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                        {
									cout<<endl<<"After execution:------------------------------------------------------------";
                           //print_order_book(bidBook, askBook);   
									//cin.get();                  
                        }*/
                   
                     }
                     break;
           case 'X': {
                     input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderCancelMessage,sizeof(orderCancelMessage));
                     map<uint64_t, order>::iterator it;
                     it = orderID_to_properties.find(static_cast<uint64_t>(o_orderCancelMessage.OID)); 
                     o_orderCancelMessage.print();
                     cin.get();	
							/*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"Before cancel:----------------------------------------"; 
     								o_orderCancelMessage.print();
                           //print_order_book(bidBook, askBook);                     
                         }*/
                      if(it == orderID_to_properties.end())
                        {
                           //cout<<endl<<"Canceling an order not in the OID map!!";
                        }
                      else
                        {
  									order tempOrder = it->second; //Order that is getting canceled
									cancel_order_book_entry(tempOrder, o_orderCancelMessage.canceledShares, bidBook, askBook);
                        }
							/*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"After cancel:----------------------------------------"; 
                           //print_order_book(bidBook, askBook);                     
                         }*/
                     }
                     break;
           case 'D': {
                     input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderDeleteMessage,sizeof(orderDeleteMessage));
                     map<uint64_t, order>::iterator it;
                     it = orderID_to_properties.find(static_cast<uint64_t>(o_orderDeleteMessage.OID)); 
o_orderDeleteMessage.print();
 							/*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"Before delete:----------------------------------------";
     								o_orderDeleteMessage.print();
                           //print_order_book(bidBook, askBook);                     
                         }*/
                      if(it == orderID_to_properties.end())
                        {
                           //cout<<endl<<"Deleting an order not in the OID map!!";
                        }
                      else
                        {
  									order tempOrder = it->second; //Order that is getting deleted
									delete_order_book_entry(tempOrder, bidBook, askBook);
                           orderID_to_properties.erase(it);
                        }
 							/*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"After delete:----------------------------------------";
                           //print_order_book(bidBook, askBook);                     
									//cin.get();
                         }*/

                     }
                     break;
           case 'U': {
                     input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_orderReplaceMessage,sizeof(orderReplaceMessage));
                     order deleteOrder;
                     map<uint64_t, order>::iterator it;
                     it = orderID_to_properties.find(static_cast<uint64_t>(o_orderReplaceMessage.originalOID)); 
                       /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"Before replace:------------------------------------------";
     								o_orderReplaceMessage.print();
                           //print_order_book(bidBook, askBook);                     
                         }*/

                      if(it == orderID_to_properties.end() && debugMode == 1)
                        {
                           //cout<<endl<<"Replacing an order not in the OID map!!";
                        }
                      else
                        {
  									order tempOrder = it->second; //Order that is getting executed
                           char originalSide = tempOrder.side;
									delete_order_book_entry(tempOrder, bidBook, askBook);
                           orderID_to_properties.erase(it);
    								tempOrder.initialize(o_orderReplaceMessage.newOID, o_orderReplaceMessage.price, 
                                          o_orderReplaceMessage.shares, originalSide);
    		                  orderID_to_properties.insert(pair<uint64_t,order>
          										                (static_cast<uint64_t>(o_orderReplaceMessage.newOID), tempOrder));
          		            add_order_book_entry(tempOrder,bidBook,askBook, 'A');
                        }
                       /*if(debugMode == 1 && !bidBook.empty() && !askBook.empty() && start_of_trading)
                         {
                           cout<<endl<<"After replace:------------------------------------------";
     								o_orderReplaceMessage.print();
                           //print_order_book(bidBook, askBook);                     
                           //cin.get();
                         }*/

                     }
                     break;
           case 'P': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_tradeMessageNonCross,sizeof(tradeMessageNonCross));
                     //o_tradeMessageNonCross.convert_endian();
                     break;
           case 'Q': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_tradeMessageCross,sizeof(tradeMessageCross));
                     //o_tradeMessageCross.convert_endian();
                     break;
           case 'B': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_brokenTrade,sizeof(brokenTrade));
                     //o_brokenTrade.convert_endian();
                     //These messages can be ignored since we are only using ITCH data. Don't even have to convert endian
                     break;
           case 'I': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_netOrderImbalanceIndicator,sizeof(netOrderImbalanceIndicator));
                     //o_netOrderImbalanceIndicator.convert_endian();
                     break;
           case 'N': input_file.seekg(-1,ios::cur);
                     input_file.read((char*)&o_retailPriceImprovementIndicator,sizeof(retailPriceImprovementIndicator));
                     //o_retailPriceImprovementIndicator.convert_endian();
                     break;
           default:  break;
        }

     }
   }
 input_file.close();
 
 return 0;
}


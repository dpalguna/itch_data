#include "class_definitions.h"
void voluntary_uncross(order a_order, map<uint32_t, map<uint64_t, order> >&a_bidBook, map<uint32_t, map<uint64_t, order> >&a_askBook);

bool add_order_book_entry(order a_order, map<uint32_t, map<uint64_t, order> >&a_bidBook, map<uint32_t, 
                             map<uint64_t, order> >&a_askBook, char a_msgCode)
{
  bool unc=0;
  switch(a_msgCode)
   {
      case 'A': case 'F':
                if(a_order.side == 'B')
                  {
                     if(a_bidBook.find(a_order.price) == a_bidBook.end())//The price is not present in the book
                       {
                          if(a_askBook.empty() || a_order.price < a_askBook.begin()->first) //Direct insert if ask book empty or price right
          							{
                          			map <uint64_t, order> map_at_price;
                          			map_at_price.insert(pair<uint64_t, order>(static_cast<uint64_t>(a_order.OID),a_order));
                          			a_bidBook.insert(pair<uint32_t, map<uint64_t, order> >
                          			(static_cast<uint32_t>(a_order.price), map_at_price));
										}
                          else
                              {
         								voluntary_uncross(a_order, a_bidBook, a_askBook);
                                 unc = 1;
                              }
                       }
                     else//The price is already there
                       {
                          ((a_bidBook.find(a_order.price))->second).insert(pair<uint64_t, order>(a_order.OID,a_order));
                       }
                  }
                else//add sell order
                  {
                     if(a_askBook.find(a_order.price) == a_askBook.end())
                       {
                          if(a_bidBook.empty() || a_order.price > a_bidBook.rbegin()->first)
 									 {
                            	map <uint64_t, order> map_at_price;
                            	map_at_price.insert(pair<uint64_t, order>(static_cast<uint64_t>(a_order.OID),a_order));
                          	 	a_askBook.insert(pair<uint32_t, map<uint64_t, order> >
                          		(static_cast<uint32_t>(a_order.price), map_at_price));
      							 }
                          else
                             {
         						   voluntary_uncross(a_order, a_bidBook, a_askBook);
                              unc = 1;
                             }
                       }
                     else
                       {
                         ((a_askBook.find(a_order.price))->second).insert(pair<uint64_t, order>(a_order.OID,a_order));
                       }
                  }
     default: break;
   }
  return unc;
}

bool execute_order_book_entry(order a_executedOrder, uint32_t a_executedShares, map<uint32_t, map<uint64_t, order> >&a_bidBook, 
                              map<uint32_t, map<uint64_t, order> >&a_askBook)
{
  static int numViolations = 0;
  bool violatePriority = 0;
  if(a_executedOrder.side == 'B') //A buy order got executed
    {
       map<uint32_t, map<uint64_t, order> >::iterator pit = a_bidBook.find(a_executedOrder.price);
       if(pit != a_bidBook.end())
       { 
        map<uint64_t, order>::iterator oit = (pit->second).find(a_executedOrder.OID);
        if(oit != (pit->second).end())
         {  
          (oit->second).shares = ((oit->second).shares > a_executedShares)?(oit->second).shares-a_executedShares:0;
          if(oit->second.OID != ((pit->second).begin())->second.OID)
            {
              violatePriority = 1;
              ++numViolations;
              cout<<endl<<"Number of violations:"<<numViolations;
            }
          if((oit->second).shares == 0)
          {
           (pit->second).erase(oit);
           if(pit->second.empty())
            {
               a_bidBook.erase(pit);
            }
          } 
         }
       }
    }
  else //sell order got executed
    {
       map<uint32_t, map<uint64_t, order> >::iterator pit = a_askBook.find(a_executedOrder.price);
       if(pit!=a_askBook.end())
        {
        map<uint64_t, order>::iterator oit = (pit->second).find(a_executedOrder.OID);
        if(oit  != (pit->second).end())
        {
         (oit->second).shares = ((oit->second).shares > a_executedShares)?(oit->second).shares-a_executedShares:0; 
         if(oit->second.OID != ((pit->second).begin())->second.OID)
            {
              violatePriority = 1;
              ++numViolations;
              cout<<endl<<"Number of violations:"<<numViolations;
            }
         if((oit->second).shares == 0)
         {
           (pit->second).erase(oit);
           if(pit->second.empty())
            {
              a_askBook.erase(pit);
            }
         }
        }
       }
    }

  return violatePriority;
}


void cancel_order_book_entry(order a_canceledOrder, uint32_t a_canceledShares, map<uint32_t, map<uint64_t, order> >&a_bidBook, 
                              map<uint32_t, map<uint64_t, order> >&a_askBook)
{
  if(a_canceledOrder.side == 'B') //A buy order got executed
    {
       map<uint32_t, map<uint64_t, order> >::iterator pit = a_bidBook.find(a_canceledOrder.price);
       if(pit != a_bidBook.end())
       {
        map<uint64_t, order>::iterator oit = (pit->second).find(a_canceledOrder.OID);
        if(oit != (pit->second).end() )
        {
         (oit->second).shares = ((oit->second).shares > a_canceledShares)?(oit->second).shares-a_canceledShares:0; 
         if((oit->second).shares == 0)
          {
           (pit->second).erase(oit);
           if(pit->second.empty())
             {
               a_bidBook.erase(pit);
             }
          }
         } 
       }
    }
  else //sell order got executed
    {
       map<uint32_t, map<uint64_t, order> >::iterator pit = a_askBook.find(a_canceledOrder.price);
       if(pit!=a_askBook.end())
       {
        map<uint64_t, order>::iterator oit = (pit->second).find(a_canceledOrder.OID);
        (oit->second).shares = ((oit->second).shares > a_canceledShares)?(oit->second).shares-a_canceledShares:0;
        if(oit!=(pit->second).end())
         {
          if((oit->second).shares == 0)
         	{
           		(pit->second).erase(oit);
           		if(pit->second.empty())
             		{
               		a_askBook.erase(pit);
             		}

         	}
        }
       }
    }

  return;
}

void delete_order_book_entry(order a_deletedOrder, map<uint32_t, map<uint64_t, order> >&a_bidBook, 
                              map<uint32_t, map<uint64_t, order> >&a_askBook)
{
  if(a_deletedOrder.side == 'B') //A buy order got deleted
    {
       map<uint32_t, map<uint64_t, order> >::iterator pit = a_bidBook.find(a_deletedOrder.price);
       if(pit != a_bidBook.end())
       {
          map<uint64_t, order>::iterator oit = (pit->second).find(a_deletedOrder.OID);
          if(oit != (pit->second).end())
           {
             (pit->second).erase(oit);
             if(pit->second.empty())
              {
                a_bidBook.erase(pit);
              }
           }
       }
    }
  else //sell order got deleted
    {
       map<uint32_t, map<uint64_t, order> >::iterator pit = a_askBook.find(a_deletedOrder.price);
       if(pit != a_askBook.end())
        {
          map<uint64_t, order>::iterator oit = (pit->second).find(a_deletedOrder.OID);
          if(oit!=(pit->second).end())
           {
            (pit->second).erase(oit);
            if(pit->second.empty())
              {
                a_askBook.erase(pit);
              }
           }
        }
    }

  return;
}

void voluntary_uncross(order a_order, map<uint32_t, map<uint64_t, order> >&a_bidBook, map<uint32_t, map<uint64_t, order> >&a_askBook)
{
   vector<order> deletedOrders;
   order tempDelOrder;
   static int count =0;
   count++;
	if(a_order.side == 'S') //Sell order treated as a MO and uncrossed with the bid book
     {
 	      map<uint32_t, map<uint64_t, order> >::reverse_iterator pit = a_bidBook.rbegin();
			uint32_t totalShares = a_order.shares;
         while(totalShares > 0 && pit!=a_bidBook.rend())
          {
            map<uint64_t, order>::iterator oit = (pit->second).begin();
            
            while(oit!=(pit->second).end() && totalShares>0)
			     {
                 uint32_t originalTotal = totalShares;
				     totalShares = totalShares > (oit->second.shares) ? totalShares-(oit->second.shares):0;
                 oit->second.shares = originalTotal > (oit->second.shares) ? 0: oit->second.shares - originalTotal; 
                 if (oit->second.shares == 0)
                 {
						  deletedOrders.push_back(oit->second); 
                 }                       
                 oit++;
			     }
            pit++;
          }
     }
   else//uncross buy order with ask book
     {
         map<uint32_t, map<uint64_t, order> >::iterator pit = a_askBook.begin();
			uint32_t totalShares = a_order.shares;
         while(totalShares > 0 && pit!=a_askBook.end())
          {
            map<uint64_t, order>::iterator oit = (pit->second).begin();
            while(oit!=(pit->second).end() && totalShares>0)
			     {
                 uint32_t originalTotal = totalShares;
				     totalShares = totalShares > (oit->second.shares) ? totalShares-(oit->second.shares):0;
                 oit->second.shares = originalTotal > (oit->second.shares) ? 0: oit->second.shares - originalTotal; 
                 if (oit->second.shares == 0)
                   {
                     deletedOrders.push_back(oit->second);
                   }
                  oit++;
			     }
            pit++;
          }
     }
   vector<order>::iterator vit=deletedOrders.begin();
   while(vit!=deletedOrders.end())
     {
        delete_order_book_entry(*vit, a_bidBook, a_askBook);
        vit++;
     }
   //cerr<<endl<<"finished uncrossing";
   //cin.get();
   return;
}

void print_order_book(map<uint32_t, map<uint64_t, order> >&a_bidBook, map<uint32_t, map<uint64_t, order> >&a_askBook)
{
 map<uint32_t, map<uint64_t, order> >::reverse_iterator pit = a_bidBook.rbegin();
 int count = 0;
 while(pit!=a_bidBook.rend() && count<1)
   {
      cout<<endl<<(pit->first)<<":";
		map<uint64_t, order>::iterator oit = (pit->second).begin();
      while(oit!=(pit->second).end())
			{
				/*cout<<"("<<(oit->first)<<","<<(oit->second.second)<<"."<<(oit->second.nanoSecond)
            <<","<<(oit->second.price)<<","<<(oit->second.shares)<<","<<(oit->second.side)
            <<")--->";*/
            cout<<"("<<(oit->first)<<","
            <<","<<(oit->second.price)<<","<<(oit->second.shares)<<","<<(oit->second.side)
            <<")--->";
            oit++;
			}
      cout<<endl;
      pit++;
      count++;
   }
 cout<<endl<<"----------------------------------------------------------------------------------------" ;
 map<uint32_t, map<uint64_t, order> >::iterator apit = a_askBook.begin();
 count =0;
 while(apit!=a_askBook.end() && count< 1)
   {
      cout<<endl<<(apit->first)<<":";
		map<uint64_t, order>::iterator oit = (apit->second).begin();
      while(oit!=(apit->second).end())
			{
				/*cout<<"("<<(oit->first)<<","<<(oit->second.second)<<"."<<(oit->second.nanoSecond)
            <<","<<(oit->second.price)<<","<<(oit->second.shares)<<","<<(oit->second.side)
            <<")--->";*/
           cout<<"("<<(oit->first)<<","
            <<","<<(oit->second.price)<<","<<(oit->second.shares)<<","<<(oit->second.side)
            <<")--->";
            oit++;
			}
      cout<<endl;
      apit++;
      count++;
   }

 return;
}

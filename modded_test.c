#include "ttc.h"

int main()
{
	// Test 2. Read stations in from bloor_line.txt


	struct station *kipling = read_stations();
	print_stations(kipling);
	/* should print:
		The stations: 
				 Kipling (0)-> Islington     
		      Kipling -> Islington (0)-> RoyalYork     
		    Islington -> RoyalYork (0)-> OldMill       
		    RoyalYork -> OldMill (0)-> Jane          
		      OldMill -> Jane (0)-> Runnymede     
			 Jane -> Runnymede (0)-> HighPark      
		    Runnymede -> HighPark (0)-> Keele         
		     HighPark -> Keele (0)-> DundasWest    
			Keele -> DundasWest (0)-> Lansdowne     
		   DundasWest -> Lansdowne (0)-> Dufferin      
		    Lansdowne -> Dufferin (0)-> Ossington     
		     Dufferin -> Ossington (0)-> Christie      
		    Ossington -> Christie (0)-> Bathurst      
		     Christie -> Bathurst (0)-> Spadina       
		     Bathurst -> Spadina (0)-> StGeorge      
		      Spadina -> StGeorge (0)-> Bay           
		     StGeorge -> Bay (0)-> Yonge         
			  Bay -> Yonge (0)-> Sherbourne    
			Yonge -> Sherbourne (0)-> CastleFrank   
		   Sherbourne -> CastleFrank (0)-> Broadview     
		  CastleFrank -> Broadview (0)-> Chester       
		    Broadview -> Chester (0)-> Pape          
		      Chester -> Pape (0)-> Donlands      
			 Pape -> Donlands (0)-> Greenwood     
		     Donlands -> Greenwood (0)-> Coxwell       
		    Greenwood -> Coxwell (0)-> Woodbine      
		      Coxwell -> Woodbine (0)-> MainStreet    
		     Woodbine -> MainStreet (0)-> VictioriaPark 
		   MainStreet -> VictioriaPark (0)-> Warden        
		VictioriaPark -> Warden (0)-> Kennedy       
		       Warden -> Kennedy (0)
	*/
	// Test 8. Remove all stations
	printf("\n\nCREATION COMPLETE\n\n");
	//remove_all_stations(&kipling); 
	print_stations(kipling); // prints only "The stations:"
	
	printf("\n\nCONCLUDE DEALLOCATION\n");

	return 0;
}

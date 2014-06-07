/*------------------------------------------------------------------------------------------------------------------
											 Army Ban System (MySQL)

								Author: Army, Armyww, Armyw0w (same person)
								Description: An timing ban system based on MySQL.
								Version: v1.0
								Credits:
									Y_Less - Thank you for Ssscanf plugin.
									BlueG - Thank you for MySQL plugin.
				
-------------------------------------------------------------------------------------------------------------------*/				

#include <a_samp>
#include <a_mysql>
#include <sscanf2>

#if !defined BAN_LIST
	#define BAN_LIST "banlist"
#if !defined IPBAN_LIST
	#define IPBAN_LIST "ipbanlist"
#if !defined SQL_HOST
	#define SQL_HOST "93.119.26.250"
#if !defined SQL_USER
	#define SQL_USER "zp_hid5326"
#if !defined SQL_PASS
	#define SQL_PASS "kravmagafaci"
#if !defined SQL_DB
	#define SQL_DB "zp_hid5326"
#endif

#define IP_MAX (17)
#pragma tabsize 0
public OnGameModeInit() 
{
	mysql_connect(SQL_HOST, SQL_USER, SQL_DB, SQL_PASS);
	return CallLocalFunction("ABan_OnGameModeInit", "");	
}

stock A_DeleteBanIP(playerip[])
{
	new
		str			[ 200 ], aid, asd[50];
	
	format ( str , 200 , "SELECT * FROM `"#IPBAN_LIST"` WHERE `ip`='%s' ORDER BY `id` DESC" , playerip );
	mysql_query ( str );
	mysql_store_result();
	mysql_fetch_row_format(str,"|");
	mysql_fetch_field_row(asd, "id"); aid=strval(asd);
	mysql_free_result();
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `year` = '%d', `month` = '%d', `day` = '%d' WHERE `id` ='%d'" , 0, 0, 0, aid );
    mysql_query ( str );
	return 1;
}	

stock A_DeleteBan(playername[])
{
	new
		str			[ 200 ], aid, asd[50];
	
	format ( str , 200 , "SELECT * FROM `"#BAN_LIST"` WHERE `username`='%s' ORDER BY `id` DESC" , playername );
	mysql_query ( str );
	mysql_store_result();
	mysql_fetch_row_format(str,"|");
	mysql_fetch_field_row(asd, "id"); aid=strval(asd);
	mysql_free_result();
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `year` = '%d', `month` = '%d', `day` = '%d' WHERE `id` ='%d'" , 0, 0, 0, aid );
    mysql_query ( str );
	return 1;
}	

stock A_OfflineBan(playername[], year, month, day, hour, min, sec, reason[], author[])
{
	new
	    nY,     nM,     nD,
	    nH,     nMin,   nS, aid, asd[10],
		str [ 200 ];
	getdate(nY,nM,nD);
	gettime(nH,nMin,nS);
	format ( str , 200 , "INSERT INTO `"#BAN_LIST"`(`username`) VALUES ('%s')" , playername );
	mysql_query ( str );
	format ( str , 200 , "SELECT * FROM `"#BAN_LIST"` WHERE `username`='%s' ORDER BY `id` DESC" , playername );
	mysql_query ( str );
	mysql_store_result();
	mysql_fetch_row_format(str,"|");
	mysql_fetch_field_row(asd, "id"); aid=strval(asd);
	mysql_free_result();
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `actyear` = '%d', `actmonth` = '%d', `actday` = '%d' WHERE `id` ='%d'" , nY , nM , nD , aid );
    mysql_query ( str ) ;
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `acthour` = '%d', `actmin` = '%d', `actsec` = '%d' WHERE `id` ='%d'" , nH , nMin , nS , aid );
    mysql_query ( str );
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `year` = '%d', `month` = '%d', `day` = '%d' WHERE `id` ='%d'" , year , month , day , aid );
    mysql_query ( str );
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `hour` = '%d', `min` = '%d', `sec` = '%d' WHERE `id` ='%d'" , hour , min , sec , aid );
    mysql_query ( str );
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `reason` = '%s', `autor` = '%s' WHERE `id` ='%d'" , reason , author , aid );
    mysql_query ( str );
	return 1;
}

stock A_OfflineBanIP(ipn[], year, month, day, hour, min, sec, reason[], author[])
{
	new
	    nY,     nM,     nD,
	    nH,     nMin,   nS, aid, asd[20],
		str [ 200 ];
	getdate ( nY , nM , nD );
	gettime ( nH , nMin , nS );
	format ( str , 200, "INSERT INTO `"#IPBAN_LIST"`(`ip`) VALUES ('%s')", ipn);
	mysql_query ( str );
	format ( str , 200 , "SELECT * FROM `"#IPBAN_LIST"` WHERE `ip`='%s' ORDER BY `id` DESC" , ipn );
	mysql_query ( str );
	mysql_store_result();
	mysql_fetch_row_format(str,"|");
	mysql_fetch_field_row(asd, "id"); aid=strval(asd);
	mysql_free_result();
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `actyear` = '%d' WHERE `id` ='%d'", nY , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `actmonth` = '%d', `actday` = '%d' WHERE `id` ='%d'", nM , nD , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `acthour` = '%d', `actmin` = '%d', `actsec` = '%d' WHERE `id` ='%d'", nH , nMin , nS , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `year` = '%d', `month` = '%d', `day` = '%d' WHERE `id` ='%d'" , year , month , day , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `hour` = '%d', `min` = '%d', `sec` = '%d' WHERE `id` ='%d'", hour , min , sec , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `reason` = '%s', `autor` = '%s' WHERE `id` ='%d'" , reason , author , aid );
    	mysql_query ( str );
	return 1;
}
stock A_Ban(playerid, year, month, day, hour, min, sec, reason[], author[])
{
	new
	    nY,     nM,     nD,
	    nH,     nMin,   nS, aid, asd[10],
		str [ 200 ];
	getdate(nY,nM,nD);
	gettime(nH,nMin,nS);
	format ( str , 200 , "INSERT INTO `"#BAN_LIST"`(`username`) VALUES ('%s')" , GetName(playerid) );
	mysql_query ( str );
	format ( str , 200 , "SELECT * FROM `"#BAN_LIST"` WHERE `username`='%s' ORDER BY `id` DESC" , GetName(playerid) );
	mysql_query ( str );
	mysql_store_result();
	mysql_fetch_row_format(str,"|");
	mysql_fetch_field_row(asd, "id"); aid=strval(asd);
	mysql_free_result();
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `actyear` = '%d', `actmonth` = '%d', `actday` = '%d' WHERE `id` ='%d'" , nY , nM , nD , aid );
    mysql_query ( str ) ;
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `acthour` = '%d', `actmin` = '%d', `actsec` = '%d' WHERE `id` ='%d'" , nH , nMin , nS , aid );
    mysql_query ( str );
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `year` = '%d', `month` = '%d', `day` = '%d' WHERE `id` ='%d'" , year , month , day , aid );
    mysql_query ( str );
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `hour` = '%d', `min` = '%d', `sec` = '%d' WHERE `id` ='%d'" , hour , min , sec , aid );
    mysql_query ( str );
	format ( str , 200 , "UPDATE `"#BAN_LIST"` SET `reason` = '%s', `autor` = '%s' WHERE `id` ='%d'" , reason , author , aid );
    mysql_query ( str );
	return 1;
}


stock A_BanIP(playerid, year, month, day, hour, min, sec, reason[], author[])
{
	new
	    nY,     nM,     nD,
	    nH,     nMin,   nS, aid, asd[20],
		str [ 200 ],
		ip      [ 17 ];
		
	GetPlayerIp ( playerid , ip , 16 );
	getdate ( nY , nM , nD );
	gettime ( nH , nMin , nS );
	format ( str , 200, "INSERT INTO `"#IPBAN_LIST"`(`ip`) VALUES ('%s')", ip);
	mysql_query ( str );
	format ( str , 200 , "SELECT * FROM `"#IPBAN_LIST"` WHERE `ip`='%s' ORDER BY `id` DESC" , ip );
	mysql_query ( str );
	mysql_store_result();
	mysql_fetch_row_format(str,"|");
	mysql_fetch_field_row(asd, "id"); aid=strval(asd);
	mysql_free_result();
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `actyear` = '%d' WHERE `id` ='%d'", nY , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `actmonth` = '%d', `actday` = '%d' WHERE `id` ='%d'", nM , nD , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `acthour` = '%d', `actmin` = '%d', `actsec` = '%d' WHERE `id` ='%d'", nH , nMin , nS , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `year` = '%d', `month` = '%d', `day` = '%d' WHERE `id` ='%d'" , year , month , day , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `hour` = '%d', `min` = '%d', `sec` = '%d' WHERE `id` ='%d'", hour , min , sec , aid );
    	mysql_query ( str );
	format ( str , 200 , "UPDATE `"#IPBAN_LIST"` SET `reason` = '%s', `autor` = '%s' WHERE `id` ='%d'" , reason , author , aid );
    	mysql_query ( str );
	return 1;
}

stock A_CheckIPIsBanned(playerip[])
{
	new
		string			[ 200 ];
	
	format ( string , 200 , "SELECT * FROM `"#IPBAN_LIST"` WHERE `ip` = '%s'" , playerip );
	mysql_query ( string );
	mysql_store_result ( );
	times=mysql_num_rows ( );
	return times;
}

stock A_CheckNameIsBanned(playername[])
{
	new
		string			[ 200 ], times;
		
	format ( string , 200 , "SELECT * FROM `"#BAN_LIST"` WHERE `username` = '%s'" , playername );
	mysql_query ( string );
	mysql_store_result ( );
	times=mysql_num_rows ( );
	return times;
}
	
stock A_BanExpired(playerid)
{
	new
	    nY,       nM,      nD,
	    nH,       nM2,     nS,
	    eY,       eM,      eD,
	    eH,       eM2,     eS,
	    aY,       aM,      aD,
	    aH,       aM2,     aS, id,
	    string [ 200 ],
		un             [ 34 ],
	    r              [ 30 ],
	    a              [ 34 ];
		
	getdate ( nY , nM , nD );
	gettime ( nH , nM2 , nS);	
	format ( string , 200 ,"SELECT * FROM `"#BAN_LIST"` WHERE `username` = '%s' ORDER BY `id` DESC" , GetName( playerid ) );
	mysql_query ( string );
	mysql_store_result ( );
	if(mysql_num_rows ( ) != 0)
	{
		mysql_fetch_row_format ( string , "|" );
	    sscanf(string, "p<|>is[34]iiiiiiiiiiiis[30]s[34]", id, un, aY, aM, aD, aH, aM2, aS, eY, eM, eD, eH, eM2, eS, r, a);
		mysql_free_result();
		if(nY>eY)
		{
			return 0;
		}
		else
		{
			if(nY<eY) return 1;
			if(nY==eY)
			{
				if(nM>eM) return 0;
				else
				{
					if(nM<eM) return 1;
					if(nM==eM)
					{
						if(nD>eD) return 0;
						else
						{
							if(nD<eD) return 1;
							if(nD==eD)
							{
								if(nH>eH) return 0;
								else
								{
									if(nH<eH) return 1;
									if(nH==eH)
									{
										if(nM2>eM2) return 0;
										else
										{
											if(nM2<eM2) return 1;
											if(nM2==eM2)
											{
												if(nS>eS) return 0;
												else
												{
													if(nS<eS) return 1;
													if(nS==eS) return 0;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}
stock A_oBanExpired(pn[])
{
	new
	    nY,       nM,      nD,
	    nH,       nM2,     nS,
	    eY,       eM,      eD,
	    eH,       eM2,     eS,
	    aY,       aM,      aD,
	    aH,       aM2,     aS, id,
	    string [ 200 ],
		un             [ 34 ],
	    r              [ 30 ],
	    a              [ 34 ];
		
	getdate ( nY , nM , nD );
	gettime ( nH , nM2 , nS);	
	format ( string , 200 ,"SELECT * FROM `"#BAN_LIST"` WHERE `username` = '%s' ORDER BY `id` DESC" , pn );
	mysql_query ( string );
	mysql_store_result ( );
	if(mysql_num_rows ( ) != 0)
	{
		mysql_fetch_row_format ( string , "|" );
	    sscanf(string, "p<|>is[34]iiiiiiiiiiiis[30]s[34]", id, un, aY, aM, aD, aH, aM2, aS, eY, eM, eD, eH, eM2, eS, r, a);
		mysql_free_result();
		if(nY>eY)
		{
			return 0;
		}
		else
		{
			if(nY<eY) return 1;
			if(nY==eY)
			{
				if(nM>eM) return 0;
				else
				{
					if(nM<eM) return 1;
					if(nM==eM)
					{
						if(nD>eD) return 0;
						else
						{
							if(nD<eD) return 1;
							if(nD==eD)
							{
								if(nH>eH) return 0;
								else
								{
									if(nH<eH) return 1;
									if(nH==eH)
									{
										if(nM2>eM2) return 0;
										else
										{
											if(nM2<eM2) return 1;
											if(nM2==eM2)
											{
												if(nS>eS) return 0;
												else
												{
													if(nS<eS) return 1;
													if(nS==eS) return 0;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}
stock A_BanIPExpired(ipn[])
{
	new
	    nY,       nM,      nD,
	    nH,       nM2,     nS,
	    eY,       eM,      eD,
	    eH,       eM2,     eS,
	    aY,       aM,      aD,
	    aH,       aM2,     aS,	id,
	    string [ 200 ],
	    ip         [ IP_MAX ],
	    r              [ 30 ],
	    a              [ 34 ];
		
	getdate ( nY , nM , nD ), gettime ( nH , nM2 , nS );
	format ( string, 200 , "SELECT * FROM `"#IPBAN_LIST"` WHERE `ip` = '%s' ORDER BY `id` DESC" , ipn );
	mysql_query ( string ); 
	mysql_store_result ( );
	if(mysql_num_rows ( ) != 0)
	{
		mysql_fetch_row_format ( string , "|" );
	    sscanf(string, "p<|>is[16]iiiiiiiiiiiis[30]s[34]", id, ip, aY, aM, aD, aH, aM2, aS, eY, eM, eD, eH, eM2, eS, r, a);
		mysql_free_result();
		if(nY>eY)
		{
			return 0;
		}
		else
		{
			if(nY<eY) return 1;
			if(nY==eY)
			{
				if(nM>eM) return 0;
				else
				{
					if(nM<eM) return 1;
					if(nM==eM)
					{
						if(nD>eD) return 0;
						else
						{
							if(nD<eD) return 1;
							if(nD==eD)
							{
								if(nH>eH) return 0;
								else
								{
									if(nH<eH) return 1;
									if(nH==eH)
									{
										if(nM2>eM2) return 0;
										else
										{
											if(nM2<eM2) return 1;
											if(nM2==eM2)
											{
												if(nS>eS) return 0;
												else
												{
													if(nS<eS) return 1;
													if(nS==eS) return 0;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

GetName(playerid)
{
	new 
		name[ 35 ];
		
	GetPlayerName ( playerid , name , 34);
	return name;
}

stock GetMonthDays(month)
{
	switch(month)
	{
		case 1: return 31;
		case 2: return 28;
		case 3: return 31;
		case 4: return 30;
		case 5: return 31;
		case 6: return 30;
		case 7: return 31;
		case 8: return 31;
		case 9: return 30;
		case 10: return 31;
		case 11: return 30;
		case 12: return 31;
	}
	return 0;
}

forward ABan_OnGameModeInit();

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit ABan_OnGameModeInit
extern const bool DEBUG		        = true;						/**< Set true for debugging output	  */
extern const int RECORDSPERBLOCK	= 4;						/**< Maximum records for the block	  */
extern const int ZIPLENGTH		= 6;						/**< Max length of the zip code in digits */
extern const int RBNLENGTH        	= 8;						/**< Max length of the RBN code in digits */
extern const int BLOCKLENGTH      	= RBNLENGTH + RECORDSPERBLOCK * ZIPLENGTH;	/**< Maximum length for the block	  */
extern const double FILLPERCENT   	= 75;						/**< Max length of the RBN code in digits */
extern const int BLOCKFILLCOUNT		  = RECORDSPERBLOCK * (FILLPERCENT/100);		/**< Max length of the RBN code in digits */
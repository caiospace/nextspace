/* 
   Project: Player

   Author: Developer

   Created: 2019-02-21 15:58:25 +0200 by me
   
   Application Controller
*/
 
#import <AppKit/AppKit.h>

@class Player;

@interface AppController : NSObject
{
  Player *player;
}

- (void)showPrefPanel:(id)sender;

@end

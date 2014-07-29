/*
 *  Copyright (c) 2013 Bjørn Magnus Mathisen <bjornmm at me dot com>
 *
 *  tox-adium - Adium protocol plugin or Tox (see http://tox.im)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  This plugin is based on the Nullprpl mockup from Pidgin / Finch / libpurple
 *  which is disributed under GPL v2 or later.  See http://pidgin.im/
 */

#import <Foundation/Foundation.h>
#import "ToxAccount.h"

@implementation ToxAccount
- (const char*)protocolPlugin
{
    return "prpl-adium-tox";
}

/*
 - (NSSet *)supportedPropertyKeys
 {
	static NSMutableSet *supportedPropertyKeys = nil;
	
	if (!supportedPropertyKeys) {
 supportedPropertyKeys = [[NSMutableSet alloc] initWithObjects:
 @"AvailableMessage",
 @"textProfile",
 nil];
 [supportedPropertyKeys unionSet:[super supportedPropertyKeys]];
	}
	
	return supportedPropertyKeys;
 }
 */


- (NSString *)host
{
    return @"192.254.75.98";
}
@end
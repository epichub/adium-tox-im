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
#import "ToxService.h"
#import "ToxAccount.h"
#import <Adium/AISharedAdium.h>
#import <Adium/AIStatusControllerProtocol.h>
#import <AIUtilities/AIStringUtilities.h>
#import <AIUtilities/AIImageAdditions.h>

@implementation ToxService
- (Class)accountClass {
    return [ToxAccount class];
}

//Service Description
- (NSString *)serviceCodeUniqueID {
    return @"libpurple-tox";
}
- (NSString *)serviceID{
    return @"Tox";
}
- (NSString *)serviceClass {
    return @"Tox";
}
- (NSString *)shortDescription {
    return @"Tox";
}
- (NSString *)longDescription {
    return @"Tox encrypted IM protocol";
}

- (NSCharacterSet *)allowedCharacters {
    NSMutableCharacterSet *allowed = [NSMutableCharacterSet alphanumericCharacterSet];
    [allowed formUnionWithCharacterSet:[NSCharacterSet  punctuationCharacterSet]];
    [allowed formUnionWithCharacterSet:[NSCharacterSet  whitespaceCharacterSet]];
    [allowed formUnionWithCharacterSet:[NSCharacterSet  characterSetWithCharactersInString: @"|"]];
    return allowed;
}

- (NSUInteger)allowedLength {
    return 129;
}

- (BOOL)caseSensitive {
    return NO;
}
- (AIServiceImportance)serviceImportance {
    return AIServicePrimary;
}

- (NSString *)userNameLabel {
    return AILocalizedString(@"Account Name", nil); // Sign-in name
}

- (void)registerStatuses {
#define ADDSTATUS(name, type) \
[adium.statusController registerStatus:name \
withDescription:[adium.statusController localizedDescriptionForCoreStatusName:name] \
ofType:type forService:self]
    
    ADDSTATUS(STATUS_NAME_AVAILABLE, AIAvailableStatusType);
    ADDSTATUS(STATUS_NAME_BUSY, AIAvailableStatusType);
    ADDSTATUS(STATUS_NAME_AWAY, AIAwayStatusType);
    ADDSTATUS(STATUS_NAME_EXTENDED_AWAY, AIAwayStatusType);
    ADDSTATUS(STATUS_NAME_OFFLINE, AIOfflineStatusType);
}

- (NSImage *)defaultServiceIconOfType:(AIServiceIconType)iconType
{
    if ((iconType == AIServiceIconSmall) || (iconType == AIServiceIconList)) {
        return [NSImage imageNamed:@"toxicon_small" forClass:[self class] loadLazily:YES];
    } else {
        return [NSImage imageNamed:@"toxicon" forClass:[self class] loadLazily:YES];
    }
}

- (NSString *)pathForDefaultServiceIconOfType:(AIServiceIconType)iconType
{
    if ((iconType == AIServiceIconSmall) || (iconType == AIServiceIconList)) {
        return [[NSBundle bundleForClass:[self class]] pathForImageResource:@"toxicon_small"];
    }
    return [[NSBundle bundleForClass:[self class]] pathForImageResource:@"toxicon"];
}


@end
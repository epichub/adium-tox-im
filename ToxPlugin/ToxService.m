//
//  ToxService.m
//  ToxPlugin
//
//  Created by Bjørn Magnus Mathisen on 27/07/14.
//  Copyright (c) 2014 Bjorn Magnus Mathisen. All rights reserved.
//

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
    return 64;
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
        return [NSImage imageNamed:@"steam_small" forClass:[self class] loadLazily:YES];
    } else {
        return [NSImage imageNamed:@"steam" forClass:[self class] loadLazily:YES];
    }
}

- (NSString *)pathForDefaultServiceIconOfType:(AIServiceIconType)iconType
{
    if ((iconType == AIServiceIconSmall) || (iconType == AIServiceIconList)) {
        return [[NSBundle bundleForClass:[self class]] pathForImageResource:@"steam_small"];
    }
    return [[NSBundle bundleForClass:[self class]] pathForImageResource:@"steam"];
}


@end
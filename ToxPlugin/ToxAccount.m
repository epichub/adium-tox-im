//
//  ToxAccount.m
//  ToxPlugin
//
//  Created by Bjørn Magnus Mathisen on 27/07/14.
//  Copyright (c) 2014 Bjorn Magnus Mathisen. All rights reserved.
//

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
//
//  ToxPlugin.m
//  ToxPlugin
//
//  Created by Bjorn Magnus Mathisen on 21/02/14.
//  Copyright (c) 2014 Bjorn Magnus Mathisen. All rights reserved.
//

#import "ToxPlugin.h"
#import "toxprpl.h"
#import "ToxService.h"
extern void purple_init_tox_plugin();

@implementation ToxPlugin
- (void) installPlugin
{
    purple_init_tox_plugin();
    [ToxService registerService];
}

- (void) uninstallPlugin
{
    
}

- (void)installLibpurplePlugin
{
    
}
- (void)uninstallLibpurplePlugin
{
    
}
- (void)loadLibpurplePlugin
{
    
}
- (NSString *)pluginAuthor
{
    return @"Bjørn Magnus Mathisen..";
}
- (NSString *)pluginVersion
{
    return @"0.1337";
}
- (NSString *)pluginDescription
{
    return  @"heh";
}
@end

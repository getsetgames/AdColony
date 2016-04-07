//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class AdColony : ModuleRules
	{
		public AdColony(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Developer/AdColony/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
				
			PrivateIncludePathModuleNames.AddRange(
				new string[]
				{
					"Settings"
				}
				);
			
			if (Target.Platform == UnrealTargetPlatform.IOS) {
				PublicAdditionalFrameworks.Add(
					new UEBuildFramework(
						"AdColony",
						"../../lib/iOS/AdColony.embeddedframework.zip"
					)
				);

				PublicFrameworks.AddRange(
					new string[]
					{
						"AdSupport",
						"AudioToolbox",
						"AVFoundation",
						"CoreGraphics",
						"CoreMedia",
						"CoreTelephony",
						"EventKit",
						"EventKitUI",
						"MediaPlayer",
						"MessageUI",
						"QuartzCore",
						"Social",
						"StoreKit",
						"SystemConfiguration",
						"WebKit",
					}
				);

				PublicAdditionalLibraries.Add("z.1.2.5");
				
			}
		}
	}
}

// Copyright Amstad Digital 2019

using UnrealBuildTool;
using System.Collections.Generic;

public class SculptdroidTarget : TargetRules
{
	public SculptdroidTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Sculptdroid" } );
	}
}

// Copyright Amstad Digital 2019

using UnrealBuildTool;
using System.Collections.Generic;

public class SculptdroidEditorTarget : TargetRules
{
	public SculptdroidEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Sculptdroid" } );
	}
}

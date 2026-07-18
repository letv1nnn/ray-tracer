const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "ray-tracer",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });

    exe.root_module.link_libcpp = true;

    exe.root_module.addCSourceFile(.{
        .file = b.path("src/main.cpp"),
        .flags = &.{"-std=c++20"},
    });

    exe.root_module.addIncludePath(b.path("include"));

    b.installArtifact(exe);
}

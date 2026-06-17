# Installs the logos-container headers
{ pkgs, common, src }:

pkgs.stdenv.mkDerivation {
  pname = "${common.pname}-headers";
  version = common.version;

  inherit src;
  inherit (common) meta;

  # No build phase needed, just install headers
  dontBuild = true;
  dontConfigure = true;

  installPhase = ''
    runHook preInstall

    # Install headers in logos_container subdirectory
    mkdir -p $out/include/logos_container
    cp src/logos_container/*.h $out/include/logos_container/

    runHook postInstall
  '';
}

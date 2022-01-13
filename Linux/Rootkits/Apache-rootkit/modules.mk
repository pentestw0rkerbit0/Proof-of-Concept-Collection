mod_authg.la: mod_authg.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_authg.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_authg.la

# other modules required 
* entity api module is required.
* votingapi module is required.
* include/patternentity.admin.inc row 53-64 need patterns, patterns_xmlparser, patterns_yamlparser. 
	* rewrite these 12 rows can make patternentity module Independent of patterns, patterns_xmlparser, patterns_yamlparser; but instead, patternentity will depend on libraries module and the validation code on the existence of spyc&codomirror library is needed to add.
* token is actually required by Patterns module, it's not required by this module.

# reason for use votingapi
* first I can't find a module about vote quick fit our situation.
* votingapi supply a framework, smart framework. e.g. 
	* one user can vote again after two days. 
	* allow anomymous votes to vote, but forbiden too Frequently vote from the same computer.
	* wo can count how many times a user totally voted, or how many times the user voted to a centain category.

# about comments
* reply module works fine with patternentity. (though the appearance needs some improvement.)
* commentfield don't meet our requirement, because the comment field will show in the admin ui page instead of pattern view page.

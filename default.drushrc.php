<?php
/**
 * Add these options to your ~./drush/drushrc.php
 * 
 * If you don't want Drush Siteman to execute a specific task (for example
 * you don't want it to restart apache, simply comment out the line
 * 
 */

// Where do you want to set up your platforms? Any direcory is fine.
// Eclipse users - create this directory as an eclipse workspace
$options['siteman-platform-dir'] = '~/workspace/siteman/platforms';

// Makefiles
$options['siteman-makefile-dir'] = '~/workspace/siteman/makefiles';

// Apache
// To use this feature a file must be added to apache's configuration. See INSTALL.TXT
$options['siteman-apache-dir'] = '~/workspace/siteman/makefiles/apache';
$options['siteman-apache-reload'] = 'sudo /etc/init.d/apache2 reload';

// Hosts file
$options['siteman-hosts-file'] = '/etc/hosts';
$options['siteman-hosts-ip'] = '127.0.0.1';  // Add the ip you use to access to site

// Mysql 
// The Mysql user details of a user that has database create and grant rights, usually root
$options['siteman-mysql-user'] = 'root';
$options['siteman-mysql-pass'] = 'yourpassword';
$options['siteman-mysql-host'] = 'localhost';

// Eclipse
// The location of the eclipse dummy project you set up earlier. See INSTALL.TXT 
$options['siteman-dummy-project-eclipse'] = '~/workspace/siteman/platforms/eclipsedummyproject';


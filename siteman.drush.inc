<?php
// $Id$

/**
 * @file
 *   Drush Siteman.
 *
 *   Todo: Write description
 */

/**
 * Implementation of hook_drush_command().
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function siteman_drush_command() {
  $items = array();

  $items['siteman-scan'] = array(
    'description' => "Sitemanager: Scan all your sites and print a table with their locations (not implemented yet)",
    'options' => array(
      'siteman-platform-dir' => 'Tells Site Manager where your platforms are located',
    ),
    'examples' => array(
      'drush siteman-scan',
    ),
    'aliases' => array('scan'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );
  
  $items['siteman-platform-install'] = array(
    'description' => "SiteManager Platform Install will use a drush make script to install your platform in your platforms directory. Do not add .make to your makefile, it will be added automatically.",
    'arguments' => array(
      'makefile' => 'The makefile to use. Eiter a direct path to the makefile, or just the name if you specified a makefile directory in your drushrc.php or from the command line.',
    ),
    'options' => array(
      'siteman-makefile-dir' => 'Tells Site Manager where to look for your makefiles when you do a siteman-install-platform',
      'siteman-platform-dir' => 'Tells Site Manager where your platforms are located',
      'siteman-dummy-project-eclipse' => 'The location of your Eclipse Dummy Project. See docs.',
      'siteman-dummy-project-netbeans' => 'The location of your Netbeans Dummy Project. (Not Implemented yet).',
    ),
    'examples' => array(
      'drush siteman-platform-install buildkit',
      'drush smpi voicebox',
    ),
    'aliases' => array('smpi'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );

  $items['siteman-site-install'] = array(
    'description' => "SiteManager Site Install will create the settings file, the files directory and the neccesary Apache Configuration Files for a site",
    'arguments' => array(
      'sitename' => 'The sitename as it is in your drupal sites directory. ',
    ),
    
    // Todo: Add option "siteman-hosts-file" - if defined
    // this script will add a hostname for you in your hosts file
    // Todo 2: Find out what is the best way to execute "sudo". The 
    // idea is that the user must enter a password so he is 
    // aware that the hostfile is being changed, and that this
    // is a bad thing on production servers. Only to be used
    // on a local dev machine. 
    
    'options' => array(
      'siteman-platform-dir' => 'Tells Site Manager where your platforms are located',
      'siteman-apache-dir' => 'Tells Site Manager where your which Apache directory it should manage',
      'siteman-apache-reload' => 'Tells Site Manager where your which Apache directory it should manage',
      'siteman-hosts-file' => 'Tells Site Manager to update your hosts file. Sudo will be used. Do not use on a production server.',
      'siteman-mysql-user' => 'Root MySQL Username',
      'siteman-mysql-pass' => 'Root MySQL Password',
      'siteman-mysql-host' => 'MySQL Host',
    ),
    'examples' => array(
      'drush siteman-site-install www.mydevsite.com',
      'drush siteman-site-install localdev',
    ),
    'aliases' => array('smsi'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );
  
  $items['siteman-site-move'] = array(
    'description' => "Move your site to a new platform",
    'arguments' => array(
      'source_platform' => 'Under which platform the source site is located',
      'sitename' => 'The sitename as it is in your drupal sites directory. ',
      'target_platform' => 'The platform you want to move the site to',
    ),
    
    'options' => array(
      'siteman-platform-dir' => 'Tells Site Manager where your platforms are located',
      'siteman-apache-dir' => 'Tells Site Manager where your which Apache directory it should manage',
      'siteman-apache-reload' => 'Tells Site Manager where your which Apache directory it should manage',
    ),
    'examples' => array(
      'drush siteman-site-move myd7platform dev.drupal.org friendsd7platform',
      'drush siteman-site-install localdev',
    ),
    'aliases' => array('smsm'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );


  return $items;
  
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function siteman_drush_help($section) {
  switch ($section) {
    case 'drush:siteman-scan':
      return dt("This command will make you a delicious sandwich, just how you like it.");
      
    // Todo - implement other help items
  }
}


/*
 * Implementation of drush_hook_COMMAND_validate().
 */
function drush_siteman_scan_validate() {
  
}

function drush_siteman_scan($filling = 'ascii') {
 
  drush_print("\n Not implemented yet\n");
  
}

/**
 * Command: siteman-install-platform
 * 
 * Will look for your makefile.make in your "makefile directory" and 
 * run a drush make. 
 * 
 * There is a designed contraint here - your makesfile's name will be used
 * for the platform name. For example buildkit.make will become /platforms/buildkit
 * and open_atrium_mycustom.make will become /platform/open_atrium_mycustom. I want to keep
 * a 1-to-1 relationship here because once you have 50 platforms it will become
 * very difficult if you had the freedom to install any makefile to any platform name
 * 
 * @param
 *   The name of your makefile without the ".make" extension
 */
function drush_siteman_platform_install($filename = '') {

  // Todo:
  / Still in 2 minds over whether or not to force the ".make" extension
  if (file_exists($filename.'.make')) {
    drush_print('File found'); // "Look in current dir" stuff not tested
    $makefile = $filename.'.make';
  } elseif ($makefile_dir = drush_get_option('siteman-makefile-dir')) {

    if (file_exists($makefile_dir . '/' . $filename.'.make')) {
      $makefile = $makefile_dir . '/' . $filename.'.make';
      drush_print('Found Makefile in ' . $makefile);
    } 
 
  }

  if (!$makefile)
  {
    drush_set_error('DRUSH_SITEMAN_NO_MAKEFILE', dt('Makefile could not be found. Exiting.'));
    drush_die();
  }

  if (file_exists($platform_dir = drush_get_option('siteman-platform-dir'))) {
    drush_print('Installing to platform directory ' . $platform_dir);
  } else {
    $platform_dir = getcwd();
    drush_print('--siteman-platform-dir not specified, assuming current directory ' . $platform_dir);
  }

  drush_backend_invoke("make $makefile $platform_dir/$filename");

  _siteman_eclipse_config($platform_dir, $filename); // Remember $filename is the platform name

}

function drush_siteman_site_install_validate($platform = '', $sitename = '') {
  drush_print("Site Install Validate Called");
  
  // Todo: Check that correct parameters where called and stop if
  // not all options are present. Check how other modules do it,
  // pretty sure there is a "drush" way of doing it
}

/**
 * Command: siteman-site-install
 * 
 * @param
 *   The Platform to install to
 * 
 * @param
 *   The site's DNS name
 */
function drush_siteman_site_install($platform = '', $site_name = '', $overwrite = false) {

  drush_print('Searching for ' . $platform);

  $platform_dir = drush_get_option('siteman-platform-dir');

  $base_dir =  $platform_dir . (substr($platform_dir, -1) != '/' ? '/' : '') . $platform . (substr($platform, -1) != '/' ? '/' : '');

  // Todo: There is a very nice drush scan directory function 
  // that can be used here to scan for some drupal identifier
  // deeper in the directory structure. At the moment this assumes 
  // you have drupal directly installed in /your_platform_dir/platform_name/
  // and that drupal's sites file is located at /your_platform_dir/platform_name/sites.
  // We need to implement this because some people might want their actual 
  // drupal directory one level down. 

  // Todo: from wget.inc file - example how to check if '/' is required
  // $project['full_project_path'] = $project['base_project_path'] . (substr($project['base_project_path'], -1) != '/' ? '/' : '') . $project_destination_name;
  
  $sites_dir = $base_dir . 'sites';
  
  if (file_exists($sites_dir))
  {
    // Todo: Is this safe? Should we check if the / is neccesary 
    $install_dir = $sites_dir . '/'. $site_name;
    drush_print('Installing to ' . $install_dir);
  } 
  
  // Todo: The idea here is that there is a "fall-through" for the 
  // user that didn't create an drushrc.php file to configure the 
  // paths. In that case we should check for the platform in the 
  // current directory (ie "./$platform_name") so that he doesn't have to 
  // type in the option "--siteman-platform-dir=/blah/blah". I'm just not sure 
  // how drush (or php-cli) handles "what the current directory is".
  // Need to look into that and finish this section
  elseif (file_exists($platform))
  {
    drush_print('Found the platform in the current directory');
  } 
  
  // Todo: Check if the install dir exists, and ask if it should
  // be overwritten. Check wget.inc on how drush_op is used. Also
  // check the drush.inc file, there is a "confirmation" function somewhere 
  // that should be used here to ask the user "Are you sure you want to overwrite?"
  // Another question: that "are you sure..." must go in dt() right?
  
  
  if ($install_dir)
  {
    // Check if the directory exists, if so, ask the if the directory should be wiped
    // If overwrite is = TRUE this will not execute
    if (file_exists($install_dir) && !$overwrite) {
      
      // Todo: This y/n confirmation must change to give the user the options 
      // "I"gnore, or "D"elete target. This is also better than a 
      // yes/no confirmation because the user could have --yes enabled, meaning
      // he won't accidently overwrite files like in the first version. 
      $msg = dt('The destination directory already exists.');
      
      $options = array(
        'ignore' => 'Ignore: Leave files in tact and just add/update Apache Configuration',
        'delete' => 'Delete: Remove current directory and create a fresh install',
      );
      
      $choice = drush_choice($options, $msg);
      
      // Todo: Look at http://drupalcontrib.org/api/drupal/contributions--drush--includes--drush.inc/function/drush_move_dir/6
      // to see how directories and errors are handled
      
      if ($choice == 'delete' && !drush_get_context('DRUSH_SIMULATE')) {
        drush_print(dt('Deleting existing directory !install_dir', array('!install_dir' => $install_dir )));
        drush_op('drush_delete_dir', $install_dir);
        drush_shell_exec("mkdir $install_dir");
      } elseif ($choice == 'ignore') {
        $ignore_existing_site = true;
      } elseif (!$choice) {
        drush_die('Aborting');
      }
      
      
    } else {
      drush_shell_exec("mkdir $install_dir");
    }
     
    // Copy the default settings from the default dir
    if (!$ignore_existing_site) 
    {
      drush_shell_exec("cp $sites_dir/default/default.settings.php $install_dir/settings.php ");
      
      // Make the files dir
      drush_shell_exec("mkdir $install_dir/files");
      
      drush_print('Changing permissions to webserver user, please enter your sudo password');
      // Set up correct permissions as per http://drupal.org/node/244924
      drush_shell_exec("chmod 770 $install_dir/files");     
      drush_shell_exec("sudo chown www-data $install_dir/files");
      
      // Todo: Set up an option so that "www-data" in the statement above isn't hardcoded
      
      drush_shell_exec("chmod 660 $install_dir/settings.php"); // this must be 660 (and not 640) so that drupal can save the settings during install  
      drush_shell_exec("sudo chgrp www-data $install_dir/settings.php");
      
    }
    
    // Set up apache conf file 
    _siteman_apache_config($site_name, $base_dir);
    
    // Set up hosts file
    _siteman_hosts_config($site_name);
    
    // Set up mysql database
    _siteman_mysql_config($site_name);
    
  }

}

/**
 * Command: siteman-site-move
 * Move a site from one platform to the other
 * 
 * @param
 *   The Source Platform to get the file from
 * 
 * @param
 *   The site's DNS name
 * 
 * @param
 *   The Target Platform to move the site to
 * 
 */
function drush_siteman_site_move($source_platform = '', $site_name = '', $target_platform = '') {

  $platform_dir = drush_get_option('siteman-platform-dir');
  
  $source_base_dir =  $platform_dir . (substr($platform_dir, -1) != '/' ? '/' : '') . $source_platform . (substr($source_platform, -1) != '/' ? '/' : '');
  $target_base_dir =  $platform_dir . (substr($platform_dir, -1) != '/' ? '/' : '') . $target_platform . (substr($target_platform, -1) != '/' ? '/' : '');
  
  $source_sites_dir = $source_base_dir . 'sites/';
  $target_sites_dir = $target_base_dir . 'sites/';
  
  drush_move_dir($source_sites_dir.$site_name, $target_sites_dir.$site_name, false);
  
  _siteman_apache_config($site_name, $target_base_dir);
  
}


/**
 * Helper: Find a direcoty location helper
 * 
 * @param
 *   The site's DNS name
 * 
 * @param
 *   The base drupal directory (without /sites)
 */
function _siteman_find_directory_structure($site_name, $base_dir)
{
  
}



/**
 * Helper: siteman-site-install apache setup
 * 
 * @param
 *   The site's DNS name
 * 
 * @param
 *   The base drupal directory (without /sites)
 */
function _siteman_apache_config($site_name, $base_dir)
{
  $apache_dir = drush_get_option('siteman-apache-dir');
  
  if (!$apache_dir) {
    drush_print('Skipping Apache config, no --siteman-apache-dir was defined');
    return;
  }
  
  // Normalise apache dir so that it always has a slash
  $apache_dir = $apache_dir . (substr($apache_dir, -1) != '/' ? '/' : '');
  
  // Only set up apache file if apache dir is defined
  if (!file_exists($apache_dir)) {
    drush_print('Skipping Apache config, no --siteman-apache-dir was found');
    return;
  }
  
  drush_print('Apache config files found in ' . $apache_dir);
  
  // Check if the user created a file in his apache conf dir named apache.conf.tpl
  if (file_exists($apache_dir . 'apache.conf.tpl'))
  {
    $apache_config_template_filename = $apache_dir . 'apache.conf.tpl';
  } else {
    $apache_config_template_filename = dirname(__FILE__) . '/apache.conf.tpl';
  }
  
  drush_print('Using config file at ' . $apache_config_template_filename);
  
  $replace_tokens = array(
    '[DocumentRoot]' => $base_dir ,
    '[ServerName]' => $site_name,
  );
  
  $config_txt = str_replace(
    array_keys($replace_tokens),
    array_values($replace_tokens), 
    file_get_contents($apache_config_template_filename)
  );
  
  //drush_print($config_txt);
  
  // Todo: Better error checking here? Or will drush pick it up?
  file_put_contents($apache_dir . $site_name . '.conf', $config_txt);
  
  drush_print('Wrote Apache configuration file ' . $apache_dir . $site_name . '.conf');
  
  if (drush_get_option('siteman-apache-reload')) {
    drush_shell_exec(drush_get_option('siteman-apache-reload'));
  } else {
    drush_print('  --siteman-apache-reload not defined, remember to manually reload your server config.');
  }

}


/**
 * Helper: siteman-site-install hosts setup
 * 
 * @param
 *   The site's DNS name
 */
function _siteman_hosts_config($site_name) {
  
  if ( ($hosts_file = drush_get_option('siteman-hosts-file'))  && $hosts_ip = drush_get_option('siteman-hosts-ip'))
  {
    // Use sudo to echo the ip and host into the hostfile (must use sudo because hosts is usually
    // owned by root
    // Using printf instead of echo because echo isn't standard http://www.unix.com/shell-programming-scripting/56666-new-line-echo.html
    
    drush_print('Adding site to ' . $hosts_file);
    
    $line1 = "# Added by Drush Siteman. Do not add additional hosts to this line.";
    $line2 = "$hosts_ip $site_name";
    
    /* Following code is broken - if I enter the output from the drush_print below in a terminal it 
     * works perfectly, but if the script runs the exact same command it gives error "too few arguments.
     * Resorting (temporarily) to 2 echo statements below
     * 
    drush_print("sudo printf \"\\n%s\\n %s\\n\" \"$line1\" \"$line2\" >> $hosts_file");
    drush_shell_exec("sudo printf \"\\n%s\\n %s\\n\" \"$line1\" \"$line2\" >> $hosts_file");
    */
    
    /* This wont work either - sudo runs as root but the pipe is not root
     * See http://ubuntuforums.org/showthread.php?t=412329 and use the "tee" command
    drush_shell_exec("sudo echo \"$line1\" >> $hosts_file");
    drush_shell_exec("sudo echo \"$line2\" >> $hosts_file");
    */
    
    drush_shell_exec("echo \"\" | sudo tee -a $hosts_file");
    drush_shell_exec("echo \"$line1\" | sudo tee -a $hosts_file");
    drush_shell_exec("echo \"$line2\" | sudo tee -a $hosts_file"); // Yea yea this is crude and is a TODO
    
    
  } else {
    drush_print('Host file will not be updated');
  }
}


/**
 * Helper: siteman-site-install mysql setup
 * 
 * Will create a database and user permissions for that database. Prints connection
 * info. 
 * 
 * @param
 *   The site's DNS name
 */
function _siteman_mysql_config($site_name) {
  
  $mysql_user = drush_get_option('siteman-mysql-user');
  $mysql_pass = drush_get_option('siteman-mysql-pass');
  $mysql_host = drush_get_option('siteman-mysql-host');
  
  if ( (!$mysql_user || !$mysql_pass || !$mysql_host)  ) {
    drush_print('MySQL options not set, skipping database configuration');
    return;
  }
  
  $con = mysql_connect($mysql_host, $mysql_user, $mysql_pass);
  if (!$con) {
    drush_set_error('Could not connect: ' . mysql_error() . ' Please manually create database');
    return;
  }

  // Todo: Might be a good idea to support prefixes.
  // That way you can easily identify which databases are managed by sitemanager

  if (mysql_query("CREATE DATABASE `$site_name`", $con)) {
    drush_print("Database $site_name created.");
  } else {
    drush_set_error('Could not create database: ' . mysql_error() . ' Please manually create database');
  }
  
  $site_db_pass = _siteman_db_password();
  
  if (mysql_query("GRANT ALL ON `$site_name`.* TO '$site_name'@'$mysql_host' IDENTIFIED BY '$site_db_pass'", $con)) {
    drush_print("=== Your Mysql Login Details ===");
    drush_print("Host: ".$mysql_host);
    drush_print("Database: ".$site_name);
    drush_print("User: ".$site_name);
    drush_print("Password: ".$site_db_pass);
  } else {
    drush_set_error('Could not grant rights: ' . mysql_error() . ' Please manually create database user');
  }
  
  mysql_close($con);
  
}


/**
 * Helper: siteman-platform-install eclipse setup
 * 
 * Will check if an eclipse dummy project was defined, and copy
 * the eclipse project 
 * 
 * @param
 *   Your base platform directory
 * 
 * @param
 *   The platform name
 */
function _siteman_eclipse_config($base_dir, $platform_name) {
  
  // Check if eclipse variable was defined, return if not
  if ( !$eclipse_dir = drush_get_option('siteman-dummy-project-eclipse') ) {
    return;
  }
  
  if (!file_exists($eclipse_dir))
  {
    drush_set_error('DRUSH_SITEMAN_ECLIPSE_NOT_FOUND', dt('Directory specified in --siteman-dummy-project-eclipse does not exist'));
    return;
  }
  
  drush_print("Found Eclipse settings in $eclipse_dir");
  
  $platform_dir = "$base_dir/$platform_name";
  
  drush_print("Copying Eclipse project settings to $platform_dir");
  drush_print("cp -R $eclipse_dir/.* $platform_dir/");
  
  // NB, we cannot use  cp dir/.* because it will read ".." as well
  // and transverse into the parent directory
  drush_shell_exec("cp -R $eclipse_dir/.[a-zA-Z0-9]* $platform_dir/");
  
  // Next we need to fix the directory name in the .settings dir
  
  $prefs_file = "$platform_dir/.settings/org.eclipse.php.core.prefs";
  
  if (!file_exists($prefs_file))
  {
    drush_print('Eclipse prefs file not found, not renaming in projects settings directory');
    return;
  }
  
  // Get the name of the dummy project, and then replace it in the file with the 
  // new directory/project name
  $eclipse_project_name = substr($eclipse_dir, strrpos($eclipse_dir, '/') + 1);
  
  drush_print("Eclipse Project Name is " . $eclipse_project_name);
  
  $config_txt = str_replace(
    $eclipse_project_name,
    $platform_name, 
    file_get_contents($prefs_file)
  );
  
  drush_print($config_txt);
  
}



/**
 * Generates password for DB.
 * Thanks to/Credit http://ninoholic.com/simple-php-password-generator.html
 * 
 */ 
function _siteman_db_password()
{
  // Todo: Get a better password generator. This is quick but sucks - too many numeric 
  // chars and too easily guessable (attacker will know md5 was created from 2 randoms)
  return substr(md5(rand().rand()), 0, 14);
}

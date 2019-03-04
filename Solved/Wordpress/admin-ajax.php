<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', 'wordpress');

/** MySQL database username */
define('DB_USER', 'wordpress');

/** MySQL database password */
define('DB_PASSWORD', '0NYa6PBH52y86C');

/** MySQL hostname */
define('DB_HOST', '172.30.0.2');

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */

define('AUTH_KEY',         '~Xkeu-Q-}#gK[QpfqvKw#[#xL<3T2i7nf-C04mbyT{-6 tnwBVw-qw3xD`fPtFxy');
define('SECURE_AUTH_KEY',  'A=l(lh|*Yjw0c+0a3x~Rwd1p=a{X5gg3ZA)=5D?G|;z8g)k,&TH>e06L/ZCSI1u&');
define('LOGGED_IN_KEY',    '2ccB^%7@~bq%ne|uiYP6<-wSH|1wQ0eTizG|WR-e^xQet[+L|) s5g~h9zmH0_3/');
define('NONCE_KEY',        'r<gbrS~C;nR~1nl8<x_,G+WE(n)>p^V @Y|?^0_H-lXniHM|V00&.gu^oI,S+D6X');
define('AUTH_SALT',        'co2w5V-Q U_@cS!)[b+ml?d+t[ )K_Q3u~TVn-`L70L@~ay|JdLFq8!G-QOw-C,_');
define('SECURE_AUTH_SALT', 'J8oOqsxjaJ;]%uJ=a8e+]5dtWsWUp-MaEUPS_JTa9`?FDblh7+nROWQ6d*>De&;1');
define('LOGGED_IN_SALT',   'M-7bP(vP tGio^j,,<gh;w=d6)ql,sw^_`oNBQC+*cwVk>kBfj3w (v0p=%(P~sY');
define('NONCE_SALT',       'A_f+m(]3P*)pTQHU(Y~|x4GGLWc-7^s#9}]47*3=w7EBjj$&zx6bA9!oMAWT#:ie');
/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', dirname( __FILE__ ) . '/' );
}

/** Sets up WordPress vars and included files. */
require_once( ABSPATH . 'wp-settings.php' );

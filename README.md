Serial
======

Unlike Backdrop's built-in auto-increment node ID, which is global and shared
by nodes belonging to all content types, serial fields are managed per entity.
For example, the serial field of an Invoice instance will generate a unique
sequential number (starting at 1, then 2, etc.) exclusively for Invoice
instances.

The allocation of serial numbers by this module is atomic. In other words,
the serial values are unique even when multiple instances of the same entity
are created simultaneously.

Installation
------------

- Install this module using the official Backdrop CMS instructions at
  <https://backdropcms.org/guide/modules>

Usage
-----

You can add a serial field to any type at admin/content/types -> manage fields.
In the New Field form select Serial as the type of data and label and field
name as your choice, and Save. No other settings.

Notes:

Existing nodes will also get serial values when a serial field is added.
The serial token `[{entity_type}:{field_name}]` can be used with Paths.
All information about available tokens can be found at 
`admin/config/search/path/patterns` page in Replacements patterns section.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/serial/issues

Current Maintainers
-------------------

- Seeking maintainers.

Credits
-------

- Ported to Backdrop by Herb v/d Dool <https://github.com/herbdool>
- Originally developed for Drupal by colorfield <https://www.drupal.org/u/colorfield>,
colan <https://www.drupal.org/u/colan>, BR0kEN <https://www.drupal.org/u/br0ken>,
kirsh <https://www.drupal.org/u/kirsh>.

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

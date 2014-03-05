# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
 
use strict;
use warnings;
use Irssi;
 
our $VERSION = '1.00';
our %IRSSI = (
    authors => 'TeamWau Software',
    contact => '',
    name => 'wideface',
    description => 'Various IRC abuse commands',
    license => 'GPLv3 ^__________^',
);
 
# HikikomoriVampire mode
sub wideface
{
    my ($data, $server, $item) = @_;
 
    my $width = int( rand(100) );
    my $str = "^" . "_"x$width ."^";
 
    my $window = Irssi::active_win();
    my $cmd = "/say";
    $window->command( join " ", $cmd, $data, $str);
}
 
# Ran mode
sub mofusnug
{
    my ($data, $server, $item) = @_;
    my @mofusnugs = split(//, "mofusnugs");
    my $mmooffuussnnuuggss = "";
 
    for my $letter (@mofusnugs)
    {
        my $num = int(rand(4))+1;
        $mmooffuussnnuuggss .= $letter x $num;
    }
 
    my $window = Irssi::active_win();
    my $cmd = "/me";
    $window->command( join " ", $cmd, $mmooffuussnnuuggss, $data);
}
 
Irssi::command_bind('wideface', 'wideface');
Irssi::command_bind('mofusnug', 'mofusnug');
 
Irssi::print("Turns you into HikikomoriVampire, Yakumo_Ran, or, in future versions, someone else ^___________^");
Irssi::print("Usage: /wideface <your message>");
Irssi::print("Usage: /mofusnug <nick>");

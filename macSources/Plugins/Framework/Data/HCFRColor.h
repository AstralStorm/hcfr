//  ColorHCFR
//  HCFRColor.h
// -----------------------------------------------------------------------------
//  Created by J�r�me Duquennoy on 30/08/07.
//
//  $Rev: 134 $
//  $Date: 2011-02-23 22:44:34 +0000 (Wed, 23 Feb 2011) $
//  $Author: jerome $
// -----------------------------------------------------------------------------
// This program is free software; you can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation; either version 2 of the License,
// or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program; if not,
// write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// -----------------------------------------------------------------------------


#import <Cocoa/Cocoa.h>

#import <libHCFR/Color.h>
#import <HCFRPlugins/HCFRColorReference.h>
/*!
    @class
    @abstract    Repr�sente une couleur.
    @discussion  Cette classe sert d'interface pour la classe CColor de la librairie libHCFR.
*/
@interface HCFRColor : NSObject <NSCoding> {
  @private
    CColor  *color;
}
-(HCFRColor*) initWithMatrix:(Matrix)newMatrix;
-(HCFRColor*) initWithRGBMatrix:(Matrix)newMatrix colorReference:(HCFRColorReference*)reference;
-(HCFRColor*) initWithColor:(CColor)newColor;
-(id) initWithCoder:(NSCoder*)coder;

-(double) X;
-(double) Y;
-(double) Z;
/*!
    @function 
    @abstract   Retourne la luminance
    @discussion Cette fonction retourne une mesure de la luminance pour la couleur.
 On peut choisir de pr�ferer la mesure fournie par un luxm�tre extern si elle est disponible
 ou utiliser la valeur fournie par la sonde.
    @param      preferLuxmeterMeasureIfAvailable Si cet argument est � true (ou YES), la mesure
 du luxm�tre externe sera retourn�e si elle est disponible. Sinon,  la mesure de la sonde sera fournie.
    @result     La mesure de luminosit� demand�e.
*/
-(double) luminance:(bool)preferLuxmeterMeasureIfAvailable;

/*!
  @function 
   @abstract   Retourne l'instance CColor contenant les donn�es XYZ
   @discussion Cette fonction retourne une instance de CColor, qui contiend les donn�es au format
 XYZ (c'est a dire l'instance interne, sans modification)
   @result     Une variable CColor.
*/
-(CColor) XYZColor;
  /*!
  @function 
   @abstract   Retourn une instance de CColor contenant les donn�es RGB.
   @discussion 
   @result     Une variable CColor. Ce devrait �tre une matrice.
*/
-(CColor) RGBColorWithColorReference:(HCFRColorReference*)reference;
/*!
    @function 
    @abstract   Retourn le resultat de GetxyYValue de CColor
    @discussion Cette fonction est juste un pont pour son equivalent de la classe CColor
 (TODO : decrire le fonctionnement de cette fameuse fonction)
*/
-(CColor) xyYColor;
/*!
  @function 
   @abstract   Retourn le resultat de getLuminance de CColor
   @discussion Cette fonction est juste un pont pour son equivalent de la classe CColor
   (TODO : decrire le fonctionnement de cette fameuse fonction)
*/
-(double) luminance;
/*!
  @function 
   @abstract   Retourn le resultat de getColorTemp de CColor
   @discussion Cette fonction est juste un pont pour son equivalent de la classe CColor
   (TODO : decrire le fonctionnement de cette fameuse fonction)
*/
-(double) temperatureWithColorReference:(HCFRColorReference*)reference;
/*!
    @function 
    @abstract   Affiche la couleur sur la sortie standard
    @discussion Affiche les trois composantes de la couleur sur la sortie standard
*/
-(void) display;

#pragma mark Fonctions utilitaires de g�n�ration de couleurs
/*!
    @function
    @abstract   G"n�re un gris de luminausit� donn�e
    @discussion Cette fonction g�n�re un objet NSColor repr�santant une couleur grise avec la luminausit�
 demand�e.
    @param      IRE La luminausit� de la couleur � retourner, entre 0 (noir) et 100 (blanc)
    @result     Une instance autoreleased de NSColor
*/
+(NSColor*) greyNSColorWithIRE:(float)IRE;

/*!
 @function
 @abstract   G"n�re un rouge de daturation donn�e
 @discussion Cette fonction g�n�re un objet NSColor repr�santant une couleur rouge avec la saturation
 demand�e.
 @param      saturation La saturation� de la couleur � retourner, entre 0 (gris) et 100 (couleur pure)
 @result     Une instance autoreleased de NSColor
 */
+(NSColor*) redNSColorWithSaturation:(float)saturation forColorReference:(HCFRColorReference*)colorReference;

/*!
 @function
 @abstract   G"n�re un vert de daturation donn�e
 @discussion Cette fonction g�n�re un objet NSColor repr�santant une couleur vert avec la saturation
 demand�e.
 @param      saturation La saturation� de la couleur � retourner, entre 0 (gris) et 100 (couleur pure)
 @result     Une instance autoreleased de NSColor
 */
+(NSColor*) greenNSColorWithSaturation:(float)saturation forColorReference:(HCFRColorReference*)colorReference;

/*!
 @function
 @abstract   G"n�re un bleu de daturation donn�e
 @discussion Cette fonction g�n�re un objet NSColor repr�santant une couleur bleu avec la saturation
 demand�e.
 @param      saturation La saturation� de la couleur � retourner, entre 0 (gris) et 100 (couleur pure)
 @result     Une instance autoreleased de NSColor
 */
+(NSColor*) blueNSColorWithSaturation:(float)saturation forColorReference:(HCFRColorReference*)colorReference;
@end

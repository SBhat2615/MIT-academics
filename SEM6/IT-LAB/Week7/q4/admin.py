from django.contrib import admin

# Register your models here.
from q4 import models

class ProductAdmin(admin.ModelAdmin):
    list_display = ('Title', 'Price', 'Description')

admin.site.register(models.Product, ProductAdmin)
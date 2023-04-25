from django.contrib import admin

# Register your models here.
from q1 import models

class CategoryAdmin(admin.ModelAdmin):
    list_display = ('name', 'numberOfVisits', 'numberOfLikes')

class PageAdmin(admin.ModelAdmin):
    list_display = ('category', 'title', 'url', 'view')

admin.site.register(models.Category, CategoryAdmin)
admin.site.register(models.Page, PageAdmin)